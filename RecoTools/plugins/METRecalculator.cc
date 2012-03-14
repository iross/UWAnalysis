#include "UWAnalysis/RecoTools/plugins/METRecalculator.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "Math/GenVector/VectorUtil.h"

METRecalculator::~METRecalculator() 
{}

METRecalculator::METRecalculator(const edm::ParameterSet& iConfig):
  met_(iConfig.getParameter<edm::InputTag>("met")),  
  originalObjects_(iConfig.getParameter<std::vector<edm::InputTag> >("originalObjects")),  
  smearedObjects_(iConfig.getParameter<std::vector<edm::InputTag> >("smearedObjects")),  
  unclusteredScale_(iConfig.getParameter<double>("unclusteredScale")),
  threshold_(iConfig.getParameter<double>("threshold"))
{
   produces<pat::METCollection >();
}

void 
METRecalculator::beginJob()
{}

void 
METRecalculator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  //get the collection
  using namespace edm;
  using namespace reco;

  //Sum the original objects
  std::vector<std::vector<math::XYZTLorentzVector> > originalColls;

  for(unsigned int i=0;i<originalObjects_.size();++i)   {
      edm::Handle<edm::View<reco::Candidate> > objects;
      iEvent.getByLabel(originalObjects_[i],objects); 
      std::vector<math::XYZTLorentzVector> lvs;
      for(unsigned int o = 0 ;o != objects->size();++o)
	if(objects->at(o).pt()>threshold_)
	  lvs.push_back(objects->at(o).p4());

      originalColls.push_back(lvs);
  }



  std::vector<std::vector<math::XYZTLorentzVector> > smearedColls;


  for(unsigned int i=0;i<smearedObjects_.size();++i)   {
      edm::Handle<edm::View<reco::Candidate> > objects;
      iEvent.getByLabel(smearedObjects_[i],objects); 
      std::vector<math::XYZTLorentzVector> lvs;

      for(unsigned int o = 0 ;o != objects->size();++o)
	if(objects->at(o).pt()>threshold_)
	  lvs.push_back(objects->at(o).p4());

      smearedColls.push_back(lvs);
    }







  //cross clean original collection
  math::XYZTLorentzVector originalVector;
  for(unsigned int i=0;i<originalColls.size();++i)
    {

      for(unsigned int k=0;k<originalColls[i].size();++k) {
	bool pass=true;
	//for each objectloop in all previous collections and cross clean
	for(int j=0;j<(int)(i-1);++j) {
	  for(unsigned int l=0;l<originalColls[j].size();++l) 
	    if(ROOT::Math::VectorUtil::DeltaR(originalColls[i].at(k),originalColls[j].at(l))<0.2)
	      pass=false;
	}
	if(pass)
	  originalVector+=originalColls[i].at(k);
      }
    }



  math::XYZTLorentzVector smearedVector;
  for(unsigned int i=0;i<smearedColls.size();++i)
    {
      for(unsigned int k=0;k<smearedColls[i].size();++k) {
	bool pass=true;
	//for each objectloop in all previous collections and cross clean
	for(int j=0;j<(int)(i-1);++j)
	  for(unsigned int l=0;l<smearedColls[j].size();++l) 
	    if(ROOT::Math::VectorUtil::DeltaR(smearedColls[i].at(k),smearedColls[j].at(l))<0.2)
	      pass=false;
	if(pass)
	  smearedVector+=smearedColls[i].at(k);
      }
    }



  //Make the difference which is the unclustered scale

  std::auto_ptr<pat::METCollection > out(new pat::METCollection);
  Handle<pat::METCollection> srcH;
  
  if(iEvent.getByLabel(met_,srcH)) 
    for(unsigned int i=0;i<srcH->size();++i) {
      pat::MET  met = srcH->at(i);
      math::XYZTLorentzVector unclustered =-met.p4()-originalVector;
      unclustered*=unclusteredScale_;
      
      math::XYZTLorentzVector newMET = -(unclustered+smearedVector);
      met.setP4(math::XYZTLorentzVector(newMET.px(),newMET.py(),0.0,sqrt(newMET.px()*newMET.px()+newMET.py()*newMET.py())));
      out->push_back(met);
    }
  iEvent.put(out);
}


void
METRecalculator::endJob()
{}

DEFINE_FWK_MODULE(METRecalculator);
