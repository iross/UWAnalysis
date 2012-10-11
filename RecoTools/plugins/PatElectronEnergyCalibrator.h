#ifndef PatElectronEnergyCalibrator_H
#define PatElectronEnergyCalibrator_H

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "FWCore/Framework/interface/ESHandle.h"

class PatElectronEnergyCalibrator
{
 public:

  PatElectronEnergyCalibrator(std::string dataset, bool isAOD, bool isMC, 
                              bool updateEnergyError, 
                              bool debug) : dataset_(dataset),
                                            isAOD_(isAOD), isMC_(isMC), 
                                            updateEnergyError_(updateEnergyError), 
                                            energyMeasurementType_(0),
                                            debug_(debug) {}

  PatElectronEnergyCalibrator(std::string dataset, bool isAOD, bool isMC, 
                              bool updateEnergyError, uint energyMeasurementType, 
                              bool debug) : dataset_(dataset),
                                            isAOD_(isAOD), isMC_(isMC), 
                                            updateEnergyError_(updateEnergyError), 
                                            energyMeasurementType_(energyMeasurementType),
                                            debug_(debug) {}
    
  void correct(pat::Electron &, const edm::Event&, const edm::EventSetup&);
    
 private:

  void computeNewEnergy( const pat::Electron &, float r9, int run) ;
  void computeEpCombination( pat::Electron & electron ) ;
  void computeCorrectedMomentumForRegression( const pat::Electron &, float r9, int run) ;

  float newEnergy_ ;
  float newEnergyError_ ;
  
  math::XYZTLorentzVector newMomentum_ ;
  float errorTrackMomentum_ ;
  float finalMomentumError_ ;
 
  unsigned long long cacheIDTopo ;
  edm::ESHandle<CaloTopology> caloTopo ;
  
  std::string dataset_;
  bool isAOD_;
  bool isMC_;
  bool updateEnergyError_;
  uint energyMeasurementType_;
  bool debug_;
  
};

#endif


