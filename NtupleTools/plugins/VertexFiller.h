// system include files
#include <memory>
#include <vector>
// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include <TTree.h>

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "DataFormats/Common/interface/RefToBase.h"

template<class T>
reco::TransientTrack getTrack(const T& cand, const TransientTrackBuilder& builder);
template<> 
reco::TransientTrack getTrack<pat::Muon>(const pat::Muon& muon, const TransientTrackBuilder& builder) { return builder.build(muon.innerTrack()); }
template<> 
reco::TransientTrack getTrack<pat::Electron>(const pat::Electron& electron, const TransientTrackBuilder& builder) { return builder.build(electron.gsfTrack()); }
template<>
reco::TransientTrack getTrack<pat::Tau>(const pat::Tau& tau, const TransientTrackBuilder& builder) { 
	if (tau.signalPFChargedHadrCands()[0]->trackRef().isNonnull()) return (builder.build(tau.signalPFChargedHadrCands()[0]->trackRef()));
	else return (builder.build(tau.signalPFChargedHadrCands()[0]->gsfTrackRef()));
}
//
// class decleration
//
template<typename T>
class VertexFiller : public NtupleFillerBase {
	public:
		VertexFiller(){
		}


		VertexFiller(const edm::ParameterSet& iConfig, TTree* t):
			src_(iConfig.getParameter<edm::InputTag>("src")),
			tag_(iConfig.getParameter<std::string>("tag")),
			vertexTag_(iConfig.getParameter<edm::InputTag>("vertexTag"))
	{
		vdof = 0;
		vposx = 0;
		vposy = 0;
		vposz = 0;
		//		v_cxx = 0;
		//		v_cyx = 0;
		//		v_cyy = 0;
		//		v_czx = 0;
		//		v_czy = 0;
		//		v_czz = 0;
		vnormChi2 = 0;
		visValid = 0;
		z1l1SIP = 0;
		z1l2SIP = 0;
		z2l1SIP = 0;
		z2l2SIP = 0;

		t->Branch((tag_+"dof").c_str(),&vdof,(tag_+"dof/I").c_str());
		t->Branch((tag_+"x").c_str(),&vposx,(tag_+"x/F").c_str());
		t->Branch((tag_+"y").c_str(),&vposy,(tag_+"y/F").c_str());
		t->Branch((tag_+"z").c_str(),&vposz,(tag_+"z/F").c_str());
		//		t->Branch((tag_+"cxx").c_str(),&v_cxx,(tag_+"cxx/F").c_str());
		//		t->Branch((tag_+"cyx").c_str(),&v_cyx,(tag_+"cyx/F").c_str());
		//		t->Branch((tag_+"cyy").c_str(),&v_cyy,(tag_+"cyy/F").c_str());
		//		t->Branch((tag_+"czx").c_str(),&v_czx,(tag_+"czx/F").c_str());
		//		t->Branch((tag_+"czy").c_str(),&v_czy,(tag_+"czy/F").c_str());
		//		t->Branch((tag_+"czz").c_str(),&v_czz,(tag)+"czz/F").c_str());
		t->Branch((tag_+"normChi2").c_str(),&vnormChi2,(tag_+"normChi2/F").c_str());
		t->Branch((tag_+"isValid").c_str(),&visValid,(tag_+"isValid/I").c_str());
		t->Branch("z1l1SIP",&z1l1SIP,"z1l1SIP/F");
		t->Branch("z1l2SIP",&z1l2SIP,"z1l2SIP/F");
		t->Branch("z2l1SIP",&z2l1SIP,"z2l1SIP/F");
		t->Branch("z2l2SIP",&z2l2SIP,"z2l2SIP/F");
	}


		~VertexFiller()
		{ 

		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			reco::Vertex primVertex;
			edm::Handle<reco::VertexCollection> recoPVCollection;
			iEvent.getByLabel(vertexTag_, recoPVCollection);
			PrimaryVertexSorter pvs;
			bool pvfound = (recoPVCollection->size() != 0);
			if (pvfound){
				std::vector<reco::Vertex> sortedList = pvs.sortedList( *recoPVCollection.product() );
				primVertex = (sortedList.front());
			} else {
				//make dummy PV
				reco::Vertex::Point p(0,0,0);
				reco::Vertex::Error e;
				e(0,0) = 0.0015*0.0015;
				e(1,1) = 0.0015*0.0015;
				e(2,2) = 15.*15.;
				primVertex = reco::Vertex(p,e,1,1,1);
			}
			edm::Handle<std::vector<T> > handleT;
			//			if(iEvent.getByLabel(src_,handle)) {
			//				if (TransientTrackBuilder_!=0) std::cout << "!!!" << std::endl;
			//				std::cout << handle->at(0).numberOfDaughters() << std::endl;
			//				//std::cout << handleT->at(0).leg1()->pt() << std::endl;
			//				//value = handle->size();
			//				value=handle->at(0).mass();
			//			}
			edm::ESHandle<TransientTrackBuilder> myTransientTrackBuilder;
			iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",myTransientTrackBuilder);
			TransientTrackBuilder_ = myTransientTrackBuilder.product();
			std::vector<reco::TransientTrack> transientTracks;
			std::pair<bool,Measurement1D> z1l1IPpair;
			std::pair<bool,Measurement1D> z1l2IPpair;
			std::pair<bool,Measurement1D> z2l1IPpair;
			std::pair<bool,Measurement1D> z2l2IPpair;
			if(iEvent.getByLabel(src_,handleT)){
				if (handleT->size()>0){
					transientTracks.push_back(getTrack(*(handleT->at(0).leg1()->leg1()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg1()->leg2()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg2()->leg1()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg2()->leg2()), *TransientTrackBuilder_));
					z1l1IPpair = IPTools::absoluteImpactParameter3D( getTrack(*(handleT->at(0).leg1()->leg1()), *TransientTrackBuilder_), primVertex);
					z1l2IPpair = IPTools::absoluteImpactParameter3D( getTrack(*(handleT->at(0).leg1()->leg2()), *TransientTrackBuilder_), primVertex);
					z2l1IPpair = IPTools::absoluteImpactParameter3D( getTrack(*(handleT->at(0).leg2()->leg1()), *TransientTrackBuilder_), primVertex);
					z2l2IPpair = IPTools::absoluteImpactParameter3D( getTrack(*(handleT->at(0).leg2()->leg2()), *TransientTrackBuilder_), primVertex);
//					std::cout << "IP results: (val, err, sig)" << std::endl;
//					std::cout << z1l1IPpair.second.value() << " , " << z1l1IPpair.second.error() << " , " << z1l1IPpair.second.significance() << std::endl; 
//					std::cout << z1l2IPpair.second.value() << " , " << z1l2IPpair.second.error() << " , " << z1l2IPpair.second.significance() << std::endl; 
//					std::cout << z2l1IPpair.second.value() << " , " << z2l1IPpair.second.error() << " , " << z2l1IPpair.second.significance() << std::endl; 
//					std::cout << z2l2IPpair.second.value() << " , " << z2l2IPpair.second.error() << " , " << z2l2IPpair.second.significance() << std::endl; 
					if (z1l1IPpair.first) z1l1SIP = z1l1IPpair.second.significance();
					if (z1l2IPpair.first) z1l2SIP = z1l2IPpair.second.significance();
					if (z2l1IPpair.first) z2l1SIP = z2l1IPpair.second.significance();
					if (z2l2IPpair.first) z2l2SIP = z2l2IPpair.second.significance();
					KalmanVertexFitter fitter(true);
					TransientVertex myVertex = fitter.vertex(transientTracks);
					if (myVertex.isValid()){
						vposx = myVertex.position().x();
						vposy = myVertex.position().y();
						vposz = myVertex.position().z();
						vdof = myVertex.degreesOfFreedom();
						//					v_cxx = myVertex.positionError().cxx();
						//				v_cyx = myVertex.positionError().cyx();
						//					v_cyy = myVertex.positionError().cyy();
						//					v_czx = myVertex.positionError().czx();
						//				v_czy = myVertex.positionError().czy();
						//					v_czz = myVertex.positionError().czz();
						vnormChi2 = myVertex.normalisedChiSquared(); //normalised or normalized?
						visValid = myVertex.isValid();
					} else {
						vposx = 1729;
						vposy = 1729;
						vposz = 1729;
						vdof = 1729;
						//					v_cxx = myVertex.positionError().cxx();
						//				v_cyx = myVertex.positionError().cyx();
						//					v_cyy = myVertex.positionError().cyy();
						//					v_czx = myVertex.positionError().czx();
						//				v_czy = myVertex.positionError().czy();
						//					v_czz = myVertex.positionError().czz();
						vnormChi2 = 1729; 
						visValid = 1729;
					}
				}
			} else printf("Obj not found \n");
		}


	protected:
		const TransientTrackBuilder* TransientTrackBuilder_; 
		edm::InputTag src_;
		std::string tag_;
		edm::InputTag vertexTag_;
		int vdof;
		float vposx;
		float vposy;
		float vposz;
		float z1l1SIP;
		float z1l2SIP;
		float z2l1SIP;
		float z2l2SIP;
		//		float v_cxx;
		//		float v_cyx;
		//		float v_cyy;
		//		float v_czx;
		//		float v_zy;
		//		float v_zz;
		float vnormChi2;
		int visValid;
};

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef VertexFiller<PATMuMuMuMuQuad> MuMuMuMuVertexFiller;
typedef VertexFiller<PATMuMuEleEleQuad> MuMuEleEleVertexFiller;
typedef VertexFiller<PATEleEleMuMuQuad> EleEleMuMuVertexFiller;
typedef VertexFiller<PATEleEleEleEleQuad> EleEleEleEleVertexFiller;
typedef VertexFiller<PATMuMuMuTauQuad> MuMuMuTauVertexFiller;
typedef VertexFiller<PATMuMuEleTauQuad> MuMuEleTauVertexFiller;
typedef VertexFiller<PATMuMuTauTauQuad> MuMuTauTauVertexFiller;
typedef VertexFiller<PATMuMuEleMuQuad> MuMuEleMuVertexFiller;
typedef VertexFiller<PATEleEleMuTauQuad> EleEleMuTauVertexFiller;
typedef VertexFiller<PATEleEleEleTauQuad> EleEleEleTauVertexFiller;
typedef VertexFiller<PATEleEleTauTauQuad> EleEleTauTauVertexFiller;
typedef VertexFiller<PATEleEleEleMuQuad> EleEleEleMuVertexFiller;
//typedef VertexFiller<PATEleEleEleTri> EleEleEleVertexFiller;
//typedef VertexFiller<PATEleEleMuTri> EleEleMuVertexFiller;
//typedef VertexFiller<PATMuMuEleTri> MuMuEleVertexFiller;
//typedef VertexFiller<PATMuMuMuTri> MuMuMuVertexFiller;
