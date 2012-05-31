// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

//template<typename T>
class MuonCountFiller : public NtupleFillerBase {
	public:
		MuonCountFiller(){
		}


		MuonCountFiller(const edm::ParameterSet& iConfig, TTree* t):
			src_(iConfig.getParameter<edm::InputTag>("src")),
//			zzCands_(iConfig.getParameter<edm::InputTag>("zzCands")),
//			dR_(iConfig.getUntrackedParameter<double>("dR")),
			tag_(iConfig.getParameter<std::string>("tag")),
			var_(iConfig.getParameter<std::string>("method"))
	{
		value = 0;
		function = new StringCutObjectSelector<pat::Muon>(var_,true);
		t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	}


		~MuonCountFiller()
		{ 
			if(function!=0) delete function;
		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			edm::Handle<edm::View<pat::Muon> > handle;
//			edm::Handle<std::vector<T> > handleT;
			value=0;
			if(iEvent.getByLabel(src_,handle)) {
//				if(iEvent.getByLabel(zzCands_,handleT)){
					for (unsigned int i = 0; i < handle->size(); i++) {
						// check overlap with current cands
						//					}
						if ((*function)(handle->at(i))) value++; 

//				}
			}
		}
}



protected:
edm::InputTag src_;
edm::InputTag zzCands_;
double dR_;
std::string tag_;
std::string var_;
int value;
StringCutObjectSelector<pat::Muon>*function;

};

//#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
//#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
//typedef MuonCountFiller<PATMuMuMuMuQuad> MuMuMuMuMuonCountFiller;
//typedef MuonCountFiller<PATMuMuEleEleQuad> MuMuEleEleMuonCountFiller;
//typedef MuonCountFiller<PATEleEleMuMuQuad> EleEleMuMuMuonCountFiller;
//typedef MuonCountFiller<PATEleEleEleEleQuad> EleEleEleEleMuonCountFiller;
//typedef MuonCountFiller<PATMuMuMuTauQuad> MuMuMuTauMuonCountFiller;
//typedef MuonCountFiller<PATMuMuEleTauQuad> MuMuEleTauMuonCountFiller;
//typedef MuonCountFiller<PATMuMuTauTauQuad> MuMuTauTauMuonCountFiller;
//typedef MuonCountFiller<PATMuMuEleMuQuad> MuMuEleMuMuonCountFiller;
//typedef MuonCountFiller<PATEleEleMuTauQuad> EleEleMuTauMuonCountFiller;
//typedef MuonCountFiller<PATEleEleEleTauQuad> EleEleEleTauMuonCountFiller;
//typedef MuonCountFiller<PATEleEleTauTauQuad> EleEleTauTauMuonCountFiller;
//typedef MuonCountFiller<PATEleEleEleMuQuad> EleEleEleMuMuonCountFiller;
//




