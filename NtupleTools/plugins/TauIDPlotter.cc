#include "UWAnalysis/NtupleTools/plugins/TauIDPlotter.h"
#include "Math/GenVector/VectorUtil.h"
#include <string>
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


TauIDPlotter::TauIDPlotter(const edm::ParameterSet& iConfig):
  src_(iConfig.getParameter<edm::InputTag>("src")),
  srcVertices_(iConfig.getParameter<edm::InputTag>("srcVertices")),
  ref_(iConfig.getParameter<edm::InputTag>("ref")),
  discriminators_(iConfig.getParameter<std::vector<std::string> >("id")),
  ptThres_(iConfig.getUntrackedParameter<double>("threshold",0.)),
  ptNum_(iConfig.getUntrackedParameter<double>("thresholdNum",0.)),
  matchDR_(iConfig.getUntrackedParameter<double>("MatchDR",0.15)),
  bins_(iConfig.getUntrackedParameter<int>("bins",20)),
  min_(iConfig.getUntrackedParameter<double>("min",0.)),
  max_(iConfig.getUntrackedParameter<double>("max",100.))
{


  histos.push_back(fs->make<TH1F>("refPt","Reference PT",bins_,min_,max_));
  histosEta.push_back(fs->make<TH1F>("refEta","Reference Eta",bins_,-2.5,2.5));
  histosL.push_back(fs->make<TH1F>("refPtL","Reference PT(leading)",bins_,min_,max_));
  histosV.push_back(fs->make<TH1F>("refVertices","Reference Vertices",25,0,25));

  //create one more discriminator for matching!
  histos.push_back(fs->make<TH1F>("matchpt","Reference PT",bins_,min_,max_));
  histosEta.push_back(fs->make<TH1F>("matcheta","Reference eta",bins_,-2.5,2.5));
  histosL.push_back(fs->make<TH1F>("matchtL","Reference PT(leading)",bins_,min_,max_));
  histosV.push_back(fs->make<TH1F>("matchvertices","Reference Vertices",25,0,25));
  histosR.push_back(fs->make<TProfile>("matchResonse","matchResponse",25,0,25,-1.5,1.5));

  rawSummary=fs->make<TH1F>("rawSummary","Summary",discriminators_.size()+1,0,discriminators_.size()+1);
  rawSummaryL=fs->make<TH1F>("rawSummaryL","Summary",discriminators_.size()+1,0,discriminators_.size()+1);
  rawSummaryEvent=fs->make<TH1F>("rawSummaryEvent","Summary",discriminators_.size()+1,0,discriminators_.size()+1);

  rawSummary->GetXaxis()->SetBinLabel(1,"REF");
  rawSummaryL->GetXaxis()->SetBinLabel(1,"REF");
  rawSummaryEvent->GetXaxis()->SetBinLabel(1,"REF");

  for(unsigned int i=0;i<discriminators_.size();++i)
    {
      rawSummary->GetXaxis()->SetBinLabel(i+2,discriminators_[i].c_str());
      rawSummaryL->GetXaxis()->SetBinLabel(i+2,discriminators_[i].c_str());
      rawSummaryEvent->GetXaxis()->SetBinLabel(i+2,discriminators_[i].c_str());

      histos.push_back(fs->make<TH1F>((discriminators_[i]+"pt").c_str(),("Reference PT for  "+discriminators_[i]).c_str(),bins_,min_,max_));
      histosEta.push_back(fs->make<TH1F>((discriminators_[i]+"eta").c_str(),("Reference Eta for  "+discriminators_[i]).c_str(),bins_,-2.5,2.5));
      histosL.push_back(fs->make<TH1F>((discriminators_[i]+"ptL").c_str(),("Reference PT for "+discriminators_[i]).c_str(),bins_,min_,max_));
      histosV.push_back(fs->make<TH1F>((discriminators_[i]+"vertices").c_str(),("Reference Vertices for "+discriminators_[i]).c_str(),25,0,25));
      histosR.push_back(fs->make<TProfile>((discriminators_[i]+"Response").c_str(),("Response for "+discriminators_[i]).c_str(),25,0,25,-1.5,1.5));
    }

  for(unsigned int i=0;i<histos.size();++i) {
    histos[i]->Sumw2();
    histosEta[i]->Sumw2();
    histosL[i]->Sumw2();
    histosV[i]->Sumw2();
  }


}


TauIDPlotter::~TauIDPlotter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TauIDPlotter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace pat;

   edm::Handle<pat::TauCollection> src;
   edm::Handle<edm::View<Candidate> >  ref;

   //read the vertices
   float vertices=0;
   edm::Handle<VertexCollection> vertexHandle;
   if(iEvent.getByLabel(srcVertices_,vertexHandle))
     vertices =(float)( vertexHandle->size());

   //Do the probability per event
     if(iEvent.getByLabel(src_,src)) {
       rawSummaryEvent->Fill(0.);

       for(unsigned int k=0;k<discriminators_.size();++k) {
	 bool atLeastOnePassed=false;
	 for(pat::TauCollection::const_iterator i=src->begin();i!=src->end();++i) {
	   bool passed=true;
	   for(unsigned int l=0;l<=k;++l) 
	     if(i->tauID(discriminators_[l])<0.5) 
	       passed=false;
	   if(passed){
	     atLeastOnePassed=true;
	     break;
	   }
	 }
	 if(atLeastOnePassed)
	   rawSummaryEvent->Fill(k+1);
       }
     }
       
   

   if(iEvent.getByLabel(ref_,ref)&&ref->size()>0) {
     if(iEvent.getByLabel(src_,src)) {

	 for(edm::View<Candidate>::const_iterator j = ref->begin();j!=ref->end();++j)
	   if(j->pt()>ptThres_)
	     {
	       rawSummary->Fill(0.);
	       histos[0]->Fill(j->pt());
	       histosEta[0]->Fill(j->eta());
	       histosV[0]->Fill(vertices);

	       if(j==ref->begin()) {
		 histosL[0]->Fill(j->pt());
		 rawSummaryL->Fill(0.);

	       }
	       for( int k=-1;k<(int)discriminators_.size();++k) {
		 for(pat::TauCollection::const_iterator i=src->begin();i!=src->end();++i) 
		   if(ROOT::Math::VectorUtil::DeltaR(i->p4(),j->p4()) < matchDR_&&i->pt()>ptNum_) {
		     bool passed=true;
		     for( int l=0;l<=k;++l)
		       if(i->tauID(discriminators_[l])<0.5||i->pt()<ptNum_) 
			 passed=false;
		     
		     if(passed){
		       histos[k+2]->Fill(j->pt());
		       histosEta[k+2]->Fill(j->eta());
		       histosV[k+2]->Fill(vertices);
		       histosR[k+1]->Fill(vertices,(i->pt()-j->pt())/j->pt());

		       if(k>=0) {
			 rawSummary->Fill(k+1);
		       }
		       if(j==ref->begin()) {
			 histosL[k+2]->Fill(j->pt());
		       if(k>=0) 
			 rawSummaryL->Fill(k+1);
			    
		       }
		       //if one passed then break
		       break;
		     }

		   }
	       }
	     }
     }
   }
}






// ------------ method called once each job just after ending the event loop  ------------
void 
TauIDPlotter::endJob() {

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(TauIDPlotter);
