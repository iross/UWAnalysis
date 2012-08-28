// -*- C++ -*-
//
// Package:    EgammaElectronProducers
// Class:      CalibratedGsfElectronProducer
//
/**\class CalibratedGsfElectronProducer RecoEgamma/ElectronProducers/src/CalibratedGsfElectronProducer.cc

 Description: EDProducer of GsfElectron objects

 Implementation:
     <Notes on implementation>
*/

#include "UWAnalysis/RecoTools/plugins/CalibratedPatElectronProducer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/TrackCandidate/interface/TrackCandidateCollection.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "UWAnalysis/RecoTools/plugins/PatElectronEnergyCalibrator.h"

#include <iostream>

using namespace edm ;
using namespace std ;
using namespace reco ;
using namespace pat ;

CalibratedPatElectronProducer::CalibratedPatElectronProducer( const edm::ParameterSet & cfg )
// : PatElectronBaseProducer(cfg)
 {

  produces<ElectronCollection>();

  inputPatElectrons = cfg.getParameter<edm::InputTag>("inputPatElectronsTag");
  dataset = cfg.getParameter<std::string>("inputDataset");
  isMC = cfg.getParameter<bool>("isMC");
  isAOD = cfg.getParameter<bool>("isAOD");
  updateEnergyError = cfg.getParameter<bool>("updateEnergyError");
  debug = cfg.getParameter<bool>("debug");
  energyMeasurementType = cfg.getParameter<uint>("energyMeasurementType");
  //basic checks
  if (isMC&&(dataset!="Summer11"&&dataset!="Fall11"&&dataset!="Summer12"))
   { throw cms::Exception("CalibratedPatElectronProducer|ConfigError")<<"Unknown MC dataset" ; }
  if (!isMC&&(dataset!="Prompt"&&dataset!="ReReco"&&dataset!="Jan16ReReco"&&dataset!="Prompt2012"&&dataset!="ICHEP2012"))
   { throw cms::Exception("CalibratedPatElectronProducer|ConfigError")<<"Unknown Data dataset" ; }
  cout << "[CalibratedPatElectronProducer] Correcting scale for dataset " << dataset << endl;

 }
 
CalibratedPatElectronProducer::~CalibratedPatElectronProducer()
 {}

void CalibratedPatElectronProducer::produce( edm::Event & event, const edm::EventSetup & setup )
 {

  edm::Handle<edm::View<reco::Candidate> > oldElectrons ;
  event.getByLabel(inputPatElectrons,oldElectrons) ;

  std::auto_ptr<ElectronCollection> electrons( new ElectronCollection ) ;

  ElectronCollection::const_iterator electron ;
  ElectronCollection::iterator ele ;
  // first clone the initial collection
  for(edm::View<reco::Candidate>::const_iterator ele=oldElectrons->begin(); ele!=oldElectrons->end(); ++ele){    
    const pat::ElectronRef elecsRef = edm::RefToBase<reco::Candidate>(oldElectrons,ele-oldElectrons->begin()).castTo<pat::ElectronRef>();
    pat::Electron clone = *edm::RefToBase<reco::Candidate>(oldElectrons,ele-oldElectrons->begin()).castTo<pat::ElectronRef>();
    electrons->push_back(clone);
  }

  PatElectronEnergyCalibrator theEnCorrector(dataset, isAOD, isMC, updateEnergyError, energyMeasurementType, debug);

  for
   ( ele = electrons->begin() ;
     ele != electrons->end() ;
     ++ele )
   {     
     if (energyMeasurementType == 0) {
       // energy calibration for ecalDriven electrons
       if (ele->core()->ecalDrivenSeed()) {        
         theEnCorrector.correct(*ele, event, setup);
       }
       else {
         //std::cout << "[CalibratedPatElectronProducer] is tracker driven only!!" << std::endl;
       }
     } else {
       //correct all electrons for regression energy measurements
       theEnCorrector.correct(*ele, event, setup);
     }
   }
   event.put(electrons) ;

 }


#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESProducer.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
DEFINE_FWK_MODULE(CalibratedPatElectronProducer);

