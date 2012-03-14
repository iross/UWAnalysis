// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "DataFormats/Math/interface/deltaR.h"
//
// class decleration
//
template<typename T>
class JetCountFillerOL : public NtupleFillerBase {
	public:
		JetCountFillerOL(){
		}

		JetCountFillerOL(const edm::ParameterSet& iConfig, TTree* t):
			NtupleFillerBase(iConfig,t),
			src_(iConfig.getParameter<edm::InputTag>("src")),
			var_(iConfig.getParameter<std::string>("method")),
			tag_(iConfig.getParameter<std::string>("tag")),
			leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
		value = new std::vector<int>();
		singleValue=0;
		function = new StringCutObjectSelector<pat::Jet>(var_,true);
		if(!leadingOnly_)
			vbranch = t->Branch(tag_.c_str(),"std::vector<int>",&value);
		else
			vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/I").c_str());

	}


		~JetCountFillerOL()
		{ 
			if(function!=0) delete function;
		}


		void fill(const edm::Event& iEvent, const edm::EventSetup &iSetup)
		{
			edm::Handle<std::vector<T> > handle;

			singleValue=0;

			if(value->size()>0)
				value->clear();

			if(iEvent.getByLabel(src_,handle)) {
				if(leadingOnly_)
				{
					if(handle->size()>0) {
						singleValue=0;
						for(unsigned int i=0;i<handle->at(0).jets().size();++i)
							//check overlap between jets().at(j) and handle->at(0).leg1()->leg[1,2]()
//							if(reco::deltaR(pfJets.at(i)->p4(),leg1->p4())>0.5 && reco::deltaR(pfJets.at(i)->p4(),leg2->p4())>0.5)
							if((*function)(*(handle->at(0).jets().at(i)))){
								//jet passes requirements
								//see if it overlaps with our leptons
								if((reco::deltaR(handle->at(0).jets().at(i)->p4(),handle->at(0).leg1()->leg1()->p4())>0.3)&&(reco::deltaR(handle->at(0).jets().at(i)->p4(),handle->at(0).leg1()->leg2()->p4())>0.3)&&(reco::deltaR(handle->at(0).jets().at(i)->p4(),handle->at(0).leg2()->leg1()->p4())>0.3)&&(reco::deltaR(handle->at(0).jets().at(i)->p4(),handle->at(0).leg2()->leg2()->p4())>0.3))
									singleValue++;
							}
					}
				}
				else {
					if(handle->size()>0)
						for(unsigned int j=0;j<handle->size();++j) {
							singleValue=0;
							for(unsigned int i=0;i<handle->at(j).jets().size();++i)
								//check overlap between jets().at(j) and handle->at(0).leg1()->leg[1,2]()
								if((*function)(*(handle->at(j).jets().at(i)))){
									singleValue ++;
								}
							value->push_back(singleValue);
						}    
				}


			}
			else
			{
				printf("Obj not found \n");
			}
			//    vbranch->Fill();
		}


	protected:
		edm::InputTag src_;
		std::string var_;
		std::string tag_;
		bool leadingOnly_;
		std::vector<int>* value;
		int singleValue;
		StringCutObjectSelector<pat::Jet>*function;
		TBranch *vbranch;

};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef JetCountFillerOL<PATMuMuTauTauQuad> PATMuMuTauTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATMuMuMuTauQuad> PATMuMuMuTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATMuMuEleTauQuad> PATMuMuEleTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATMuMuEleMuQuad> PATMuMuEleMuQuadJetCountFillerOL;
typedef JetCountFillerOL<PATMuMuMuMuQuad> PATMuMuMuMuQuadJetCountFillerOL;
typedef JetCountFillerOL<PATMuMuEleEleQuad> PATMuMuEleEleQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleTauTauQuad> PATEleEleTauTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleEleTauQuad> PATEleEleEleTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleMuTauQuad> PATEleEleMuTauQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleEleMuQuad> PATEleEleEleMuQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleEleEleQuad> PATEleEleEleEleQuadJetCountFillerOL;
typedef JetCountFillerOL<PATEleEleMuMuQuad> PATEleEleMuMuQuadJetCountFillerOL;



