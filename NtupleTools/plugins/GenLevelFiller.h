#ifndef GENFILL_H_
#define GENFILL_H_

// system include files
#include <memory>

// user include files
#include <TTree.h>

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <math.h>
#include "Math/GenVector/VectorUtil.h"

#include "DataFormats/Candidate/interface/Candidate.h"


class GenLevelFiller : public edm::EDAnalyzer
{
    private:
        edm::InputTag gensrc_;

        double hPt, hMass, hEta, hPhi;
        double zPt[2], zMass[2], zEta[2], zPhi[2];
		double lPt[4], lEta[4], lPhi[4];
		int lPdgId[4];

        TTree * tree;

        virtual void beginJob();
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();


    public:
        explicit GenLevelFiller(const edm::ParameterSet& iConfig);
  
        ~GenLevelFiller();
};

#endif
