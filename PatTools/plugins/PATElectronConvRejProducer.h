// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
// 
/**\class PATMuonTrackVetoSelector PATMuonTrackVetoSelector.cc UWAnalysis/PATMuonTrackVetoSelector/src/PATMuonTrackVetoSelector.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: PATElectronConvRejProducer.h,v 1.4 2011/02/01 20:56:29 bachtis Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
//
// class decleration

#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"


class PATElectronConvRejProducer : public edm::EDProducer {
   public:

  

  explicit PATElectronConvRejProducer(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    tracks_(iConfig.getParameter<edm::InputTag>("tracks")),
    gsftracks_(iConfig.getParameter<edm::InputTag>("gsftracks")),
    isData_(iConfig.getParameter<bool>("isData"))
     {
       produces<std::vector<pat::Electron> >();
     }

  ~PATElectronConvRejProducer() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    double evt_bField;

    edm::Handle<DcsStatusCollection> dcsHandle;
    iEvent.getByLabel("scalersRawToDigi", dcsHandle);
    if (isData_) {
      float currentToBFieldScaleFactor = 2.09237036221512717e-04;
      float current = (*dcsHandle)[0].magnetCurrent();
      evt_bField = current*currentToBFieldScaleFactor;
    }
    else {
        
      ESHandle<MagneticField> magneticField;
      iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
        
      evt_bField = magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
    }



    edm::Handle<TrackCollection> trackH;
    iEvent.getByLabel(tracks_,trackH);



    edm::Handle<GsfTrackCollection> gsftrackH;
    iEvent.getByLabel(gsftracks_,gsftrackH);



    std::auto_ptr<pat::ElectronCollection> out( new pat::ElectronCollection);

    edm::Handle<pat::ElectronCollection> electrons;
    if(iEvent.getByLabel(src_,electrons)) 
      for(unsigned int i=0;i<electrons->size();++i) {
	pat::Electron electron = electrons->at(i);
	ConversionFinder convFinder;
	ConversionInfo convInfo = convFinder.getConversionInfo(electron, trackH,gsftrackH, evt_bField);
	if(convInfo.conversionPartnerCtfTk().isNonnull()) {
	electron.addUserFloat("convDist",convInfo.dist());
	electron.addUserFloat("convDCotTheta",convInfo.dcot());
	}
	else if(convInfo.conversionPartnerGsfTk().isNonnull()) {
	  electron.addUserFloat("convDist",convInfo.dist());
	  electron.addUserFloat("convDCotTheta",convInfo.dcot());
	}
	else
	  {
	    electron.addUserFloat("convDist",-9999);
	    electron.addUserFloat("convDCotTheta",-9999);

	  }  

	out->push_back(electron);
      }
      

    iEvent.put(out);



  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      edm::InputTag tracks_;
      edm::InputTag gsftracks_;
      bool isData_;

};

