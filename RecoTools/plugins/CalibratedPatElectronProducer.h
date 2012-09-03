#ifndef CalibratedPatElectronProducer_h
#define CalibratedPatElectronProducer_h

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/EDProduct.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

class CalibratedPatElectronProducer: public edm::EDProducer 
 {
  public:

    //static void fillDescriptions( edm::ConfigurationDescriptions & ) ;

    explicit CalibratedPatElectronProducer( const edm::ParameterSet & ) ;
    virtual ~CalibratedPatElectronProducer();
    virtual void produce( edm::Event &, const edm::EventSetup & ) ;

  private:

    edm::InputTag inputPatElectrons ;
    std::string dataset ;
    bool isAOD ;
    bool isMC ;
    bool updateEnergyError ;
    bool debug ;
    uint energyMeasurementType;
    
 } ;

#endif
