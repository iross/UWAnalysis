//todo: update all these stupid numbers.

#include "UWAnalysis/RecoTools/plugins/PatElectronEnergyCalibrator.h"

#include <CLHEP/Random/RandGaussQ.h>
#include <CLHEP/Random/Random.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"

/****************************************************************************
 *
 * Propagate SC calibration from Zee fit to the electrons
 *
 ****************************************************************************/

using namespace edm;

void PatElectronEnergyCalibrator::correct
 ( pat::Electron & electron, const edm::Event& event, const edm::EventSetup& eventSetup)

 {

  // compute r9
  float e3x3=electron.userFloat("e3x3");
  float r9 = e3x3/electron.r9();

  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE pt, eta, phi " << electron.p4().pt() << " " <<
    electron.p4().eta() << " " << electron.p4().phi() << std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE ecalEnergy, tkMonemtum, 4momentum " << 
   electron.ecalEnergy() << " " << electron.trackMomentumAtVtx().R() << " " <<
   electron.p4().t() << std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE  E/p, E/p error "<<
    electron.eSuperClusterOverP()<<" "<<sqrt(
                 (electron.ecalEnergyError()/electron.trackMomentumAtVtx().R())*(electron.ecalEnergyError()/electron.trackMomentumAtVtx().R()) +
                 (electron.ecalEnergy()*electron.trackMomentumError()/electron.trackMomentumAtVtx().R()/electron.trackMomentumAtVtx().R())*
                 (electron.ecalEnergy()*electron.trackMomentumError()/electron.trackMomentumAtVtx().R()/electron.trackMomentumAtVtx().R()))<<std::endl;
  

  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE isEB, isEE, isEBEEgap " << electron.isEB() << " " <<
   electron.isEE() << " " << electron.isEBEEGap() << std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE R9, class " << r9 << " " << 
   electron.classification() << std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] BEFORE comb momentum error " << electron.p4Error(reco::GsfElectron::P4_COMBINATION) << std::endl;


  // apply ECAL calibration scale and smearing factors depending on period and categories
  if (energyMeasurementType_ == 0) {
    computeNewEnergy(electron, r9, event.run()) ;
    //electron.correctEcalEnergy(newEnergy_,newEnergyError_) ;
    // apply E-p combination
    computeEpCombination(electron) ;
  }
  else if (energyMeasurementType_ == 1 
           || energyMeasurementType_ == 2 
           || energyMeasurementType_ == 3
           || energyMeasurementType_ == 4 ) {
    computeCorrectedMomentumForRegression(electron, event.run()) ;
  } else {
    std::cout << "Error: energyMeasurementType " << energyMeasurementType_ << " is not supported.\n";
  }
  
  electron.correctMomentum(newMomentum_,errorTrackMomentum_,finalMomentumError_);     
  
  if (debug_) std::cout << "[ElectronEnergCorrector] AFTER ecalEnergy, new comb momentum " << newEnergy_ << " " << electron.p4(reco::GsfElectron::P4_COMBINATION).t() << std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] AFTER  E/p, E/p error "<<
    electron.eSuperClusterOverP()<<" "<<sqrt(
                         (electron.ecalEnergyError()/electron.trackMomentumAtVtx().R())*(electron.ecalEnergyError()/electron.trackMomentumAtVtx().R()) +
                         (electron.ecalEnergy()*electron.trackMomentumError()/electron.trackMomentumAtVtx().R()/electron.trackMomentumAtVtx().R())*
                         (electron.ecalEnergy()*electron.trackMomentumError()/electron.trackMomentumAtVtx().R()/electron.trackMomentumAtVtx().R()))<<std::endl;
  if (debug_) std::cout << "[ElectronEnergCorrector] AFTER comb momentum error " << electron.p4Error(reco::GsfElectron::P4_COMBINATION) << std::endl;
 }

void PatElectronEnergyCalibrator::computeNewEnergy
 ( const pat::Electron & electron, float r9, int run)
 {
  //double scEnergy = electron.superCluster()->energy() ;
  double scEnergy = electron.ecalEnergy() ;
  float corr=0., scale=1.;
  float dsigMC=0., corrMC=0.;
  newEnergyError_ = electron.ecalEnergyError() ;

  // Compute correction depending on run, categories and dataset
  // Corrections for the PromptReco from R. Paramattti et al.
  //   https://indico.cern.ch/getFile.py/access?contribId=7&sessionId=1&resId=0&materialId=slides&confId=155805 (Oct03, PromptV6, 05Aug, 05Jul)
  //   https://indico.cern.ch/getFile.py/access?contribId=2&resId=0&materialId=slides&confId=149567 (PromptV5)
  //   https://indico.cern.ch/getFile.py/access?contribId=2&resId=0&materialId=slides&confId=149567 (05Jul)
  //   https://hypernews.cern.ch/HyperNews/CMS/get/AUX/2011/07/06/16:50:04-57776-ScaleAndResolution_20110706.pdf (May10+PromptV4)
  // Correction for the ReReco from R. paramatti et al. (private communication, AN in preparation)
  // Corrections for PromptReco are run and R9 dependant, corrections for the ReReco are categories or EB+/EB-/EE+/EE- dependant
  // Correction for MC is a gaussian smearing for the resolution, averaged from the results over the three periods
   edm::Service<edm::RandomNumberGenerator> rng;
   if ( ! rng.isAvailable()) {
     throw cms::Exception("Configuration")
       << "XXXXXXX requires the RandomNumberGeneratorService\n"
          "which is not present in the configuration file.  You must add the service\n"
          "in the configuration file or remove the modules that require it.";
   }
  
  // data corrections 
  if (!isMC_) {
    // corrections for prompt
    if (dataset_=="Prompt") {
      if (run>=160431 && run<=167784) {
    if (electron.isEB()) {
      if (run>=160431 && run<=163869) {
            if (r9>=0.94) corr = +0.0047;
            if (r9<0.94) corr = -0.0025;
      } else if (run>=165071 && run<=165970) {
            if (r9>=0.94) corr = +0.0007;
            if (r9<0.94) corr = -0.0049;
      } else if (run>=165971 && run<=166502) {
            if (r9>=0.94) corr = -0.0003;
            if (r9<0.94) corr = -0.0067;
      } else if (run>=166503 && run<=166861) {
            if (r9>=0.94) corr = -0.0011;
            if (r9<0.94) corr = -0.0063;
      } else if (run>=166862 && run<=167784) {
            if (r9>=0.94) corr = -0.0014;
            if (r9<0.94) corr = -0.0074;
      } 
    } else if (electron.isEE()) {
      if (run>=160431 && run<=163869) {
            if (r9>=0.94) corr = -0.0058;
            if (r9<0.94) corr = +0.0010;
      } else if (run>=165071 && run<=165970) {
            if (r9>=0.94) corr = -0.0249;
            if (r9<0.94) corr = -0.0062;
      } else if (run>=165971 && run<=166502) {
            if (r9>=0.94) corr = -0.0376;
            if (r9<0.94) corr = -0.0133;
      } else if (run>=166503 && run<=166861) {
            if (r9>=0.94) corr = -0.0450;
            if (r9<0.94) corr = -0.0178;
      } else if (run>=166862 && run<=167784) {
            if (r9>=0.94) corr = -0.0561;
            if (r9<0.94) corr = -0.0273;
      } 
    }    
      } else if (run>=1700053 && run <=172619) {
    if (electron.isEB()) {
      if (r9>=0.94) corr = -0.0011;
      if (r9<0.94) corr = -0.0067;
    } else if (electron.isEE()) {
      if (r9>=0.94) corr = +0.0009;
      if (r9<0.94) corr = -0.0046;
    }  
      } else if (run>=172620 && run <=175770) {
    if (electron.isEB()) {
      if (r9>=0.94) corr = -0.0046;
      if (r9<0.94) corr = -0.0104;
    } else if (electron.isEE()) {
      if (r9>=0.94) corr = +0.0337;
      if (r9<0.94) corr = +0.0250;
        }  
      } else if (run>=175860 && run<=177139) {                      // prompt-v1 corrections for 2011B [ 175860 - 177139 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0228;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0118;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0075;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0034;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0041;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0019;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0147;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0168;
      } else if (run>=177140 && run<=178421) {                      // prompt-v1 corrections for 2011B [ 177140 - 178421 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0239;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0129;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0079;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0038;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0011;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0049;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0236;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0257;
      } else if (run>=178424 && run<=180252) {                      // prompt-v1 corrections for 2011B [ 178424 - 180252 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0260;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0150;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0094;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0052;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0050;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0009;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0331;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0353;
      } 
    // corrections for rereco  
    } else if (dataset_=="ReReco") {                     // corrections for ReReco
      // values from https://indico.cern.ch/conferenceDisplay.py?confId=146386
      if (run>=160329 && run <=168437) {                 // Jul05 period 160329-168437
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0150;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0039;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0014;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = +0.0028;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0050;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0010;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = -0.0025;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = -0.0005;
      } else if (run>=170053 && run <=172619) {          // Aug05 period 170053-172619
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0191;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0081;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0030;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = +0.0012;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = +0.0052;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0113;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0041;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0062;
      } else if (run>=172620 && run <=175770) {          // Oct03 period
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0150;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0039;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = +0.0001;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = +0.0043;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = +0.0001;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0062;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0026;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0048;
      } else if (run>=175860 && run<=177139) {                      // prompt-v1 corrections for 2011B [ 175860 - 177139 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0228;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0118;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0075;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0034;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0041;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0019;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0147;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0168;
      } else if (run>=177140 && run<=178421) {                      // prompt-v1 corrections for 2011B [ 177140 - 178421 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0239;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0129;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0079;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0038;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0011;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0049;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0236;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0257;
      } else if (run>=178424 && run<=180252) {                      // prompt-v1 corrections for 2011B [ 178424 - 180252 ]
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) corr = -0.0260;
        if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) corr = -0.0150;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) corr = -0.0094;
        if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) corr = -0.0052;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) corr = -0.0050;
        if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) corr = +0.0009;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) corr = +0.0331;
        if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) corr = +0.0353;
      } 
    // corrections for januray 16 rereco  
    } else if (dataset_=="Jan16ReReco") {                     // corrections for january 16 ReReco
      // values from http://indico.cern.ch/getFile.py/access?contribId=2&resId=0&materialId=slides&confId=176520
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) {
        if (run>=160431 && run<=167913) corr = -0.0014; 
    if (run>=170000 && run<=172619) corr = -0.0016;   
    if (run>=172620 && run<=173692) corr = -0.0017;  
    if (run>=175830 && run<=177139) corr = -0.0021;
    if (run>=177140 && run<=178421) corr = -0.0025;
    if (run>=178424 && run<=180252) corr = -0.0024;
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) {      
        if (run>=160431 && run<=167913) corr = 0.0059; 
    if (run>=170000 && run<=172619) corr = 0.0046;   
    if (run>=172620 && run<=173692) corr = 0.0045;  
    if (run>=175830 && run<=177139) corr = 0.0042;
    if (run>=177140 && run<=178421) corr = 0.0038;
    if (run>=178424 && run<=180252) corr = 0.0039;
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) {      
        if (run>=160431 && run<=167913) corr = -0.0045; 
    if (run>=170000 && run<=172619) corr = -0.0066;   
    if (run>=172620 && run<=173692) corr = -0.0058;  
    if (run>=175830 && run<=177139) corr = -0.0073;
    if (run>=177140 && run<=178421) corr = -0.0075;
    if (run>=178424 && run<=180252) corr = -0.0071;
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) {      
        if (run>=160431 && run<=167913) corr = 0.0084; 
    if (run>=170000 && run<=172619) corr = 0.0063;   
    if (run>=172620 && run<=173692) corr = 0.0071;  
    if (run>=175830 && run<=177139) corr = 0.0056;
    if (run>=177140 && run<=178421) corr = 0.0054;
    if (run>=178424 && run<=180252) corr = 0.0058;
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) {
        if (run>=160431 && run<=167913) corr = -0.0082; 
    if (run>=170000 && run<=172619) corr = -0.0025;   
    if (run>=172620 && run<=173692) corr = -0.0035;  
    if (run>=175830 && run<=177139) corr = -0.0017;
    if (run>=177140 && run<=178421) corr = -0.0010;
    if (run>=178424 && run<=180252) corr = 0.0030;
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) {      
        if (run>=160431 && run<=167913) corr = -0.0033; 
    if (run>=170000 && run<=172619) corr = 0.0024;   
    if (run>=172620 && run<=173692) corr = 0.0014;  
    if (run>=175830 && run<=177139) corr = 0.0032;
    if (run>=177140 && run<=178421) corr = 0.0040;
    if (run>=178424 && run<=180252) corr = 0.0079;
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) {      
        if (run>=160431 && run<=167913) corr = -0.0064; 
    if (run>=170000 && run<=172619) corr = -0.0046;   
    if (run>=172620 && run<=173692) corr = -0.0029;  
    if (run>=175830 && run<=177139) corr = -0.0040;
    if (run>=177140 && run<=178421) corr = -0.0050;
    if (run>=178424 && run<=180252) corr = -0.0059;
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) {      
        if (run>=160431 && run<=167913) corr = 0.0042; 
    if (run>=170000 && run<=172619) corr = 0.0060;   
    if (run>=172620 && run<=173692) corr = 0.0077;  
    if (run>=175830 && run<=177139) corr = 0.0067;
    if (run>=177140 && run<=178421) corr = 0.0056;
    if (run>=178424 && run<=180252) corr = 0.0047;
      } 
    // corrections for 2012A and 2012B 
    } else if (dataset_=="ICHEP2012") {                     
      // values from https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/873.html   
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9<0.94) {
        if (run>=190450 && run<=190781) scale = 1.0021; 
    if (run>=190782 && run<=190949) scale = 1.0154;   
    if (run>=190950 && run<=191833) scale = 1.0046;   
    if (run>=191834 && run<=193686) scale = 1.0017;   
    if (run>=193746 && run<=194210) scale = 1.0020;   
    if (run>=194211 && run<=194479) scale = 1.0037;   
    if (run>=194480 && run<=195147) scale = 1.0047;   
    if (run>=195148 && run<=195350) scale = 1.0053;   
    if (run>=195396 && run<=195530) scale = 1.0042;   
    if (run>=195531 && run<=196531) scale = 0.9981;   
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())<1 and r9>=0.94) {      
        if (run>=190450 && run<=190781) scale = 0.9962; 
    if (run>=190782 && run<=190949) scale = 1.0096;   
    if (run>=190950 && run<=191833) scale = 0.9988;   
    if (run>=191834 && run<=193686) scale = 0.9958;   
    if (run>=193746 && run<=194210) scale = 0.9962;   
    if (run>=194211 && run<=194479) scale = 0.9979;   
    if (run>=194480 && run<=195147) scale = 0.9989;   
    if (run>=195148 && run<=195350) scale = 0.9995;   
    if (run>=195396 && run<=195530) scale = 0.9984;   
    if (run>=195531 && run<=196531) scale = 0.9922;   
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9<0.94) {      
        if (run>=190450 && run<=190781) scale = 1.0133; 
    if (run>=190782 && run<=190949) scale = 0.9997;   
    if (run>=190950 && run<=191833) scale = 1.0134;   
    if (run>=191834 && run<=193686) scale = 1.0104;   
    if (run>=193746 && run<=194210) scale = 1.0094;   
    if (run>=194211 && run<=194479) scale = 1.0118;   
    if (run>=194480 && run<=195147) scale = 1.0137;   
    if (run>=195148 && run<=195350) scale = 1.0142;   
    if (run>=195396 && run<=195530) scale = 1.0129;   
    if (run>=195531 && run<=196531) scale = 1.0065;   
      } else if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 and r9>=0.94) {      
        if (run>=190450 && run<=190781) scale = 1.0020; 
    if (run>=190782 && run<=190949) scale = 0.9883;   
    if (run>=190950 && run<=191833) scale = 1.0021;   
    if (run>=191834 && run<=193686) scale = 0.9991;   
    if (run>=193746 && run<=194210) scale = 0.9980;   
    if (run>=194211 && run<=194479) scale = 1.0005;   
    if (run>=194480 && run<=195147) scale = 1.0024;   
    if (run>=195148 && run<=195350) scale = 1.0029;   
    if (run>=195396 && run<=195530) scale = 1.0016;   
    if (run>=195531 && run<=196531) scale = 0.9951;   
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9<0.94) {
        if (run>=190450 && run<=190781) scale = 0.9989; 
    if (run>=190782 && run<=190949) scale = 1.0123;   
    if (run>=190950 && run<=191833) scale = 1.0042;   
    if (run>=191834 && run<=193686) scale = 1.0037;   
    if (run>=193746 && run<=194210) scale = 1.0047;   
    if (run>=194211 && run<=194479) scale = 1.0037;   
    if (run>=194480 && run<=195147) scale = 1.0030;   
    if (run>=195148 && run<=195350) scale = 1.0051;   
    if (run>=195396 && run<=195530) scale = 1.0003;   
    if (run>=195531 && run<=196531) scale = 1.0052;   
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())<2 and r9>=0.94) {      
        if (run>=190450 && run<=190781) scale = 0.9931; 
    if (run>=190782 && run<=190949) scale = 1.0066;   
    if (run>=190950 && run<=191833) scale = 0.9985;   
    if (run>=191834 && run<=193686) scale = 0.9979;   
    if (run>=193746 && run<=194210) scale = 0.9990;   
    if (run>=194211 && run<=194479) scale = 0.9979;   
    if (run>=194480 && run<=195147) scale = 0.9972;   
    if (run>=195148 && run<=195350) scale = 0.9994;   
    if (run>=195396 && run<=195530) scale = 0.9945;   
    if (run>=195531 && run<=196531) scale = 0.9994;   
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9<0.94) {      
        if (run>=190450 && run<=190781) scale = 1.0052; 
    if (run>=190782 && run<=190949) scale = 1.0077;   
    if (run>=190950 && run<=191833) scale = 0.9900;   
    if (run>=191834 && run<=193686) scale = 0.9893;   
    if (run>=193746 && run<=194210) scale = 1.0042;   
    if (run>=194211 && run<=194479) scale = 1.0036;   
    if (run>=194480 && run<=195147) scale = 1.0069;   
    if (run>=195148 && run<=195350) scale = 1.0133;   
    if (run>=195396 && run<=195530) scale = 0.9999;   
    if (run>=195531 && run<=196531) scale = 1.0475;   
      } else if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 and r9>=0.94) {      
        if (run>=190450 && run<=190781) scale = 0.9899; 
    if (run>=190782 && run<=190949) scale = 0.9924;   
    if (run>=190950 && run<=191833) scale = 0.9745;   
    if (run>=191834 && run<=193686) scale = 0.9738;   
    if (run>=193746 && run<=194210) scale = 0.9889;   
    if (run>=194211 && run<=194479) scale = 0.9883;   
    if (run>=194480 && run<=195147) scale = 0.9916;   
    if (run>=195148 && run<=195350) scale = 0.9982;   
    if (run>=195396 && run<=195530) scale = 0.9845;   
    if (run>=195531 && run<=196531) scale = 1.0329;   
      } 
    }  
  } 
    // MC smearing dsig is needed also for data for theenergy error, take it from the last MC values consistant
    // with the data choice
    if (dataset_=="Summer11"||dataset_=="ReReco") { // values from https://indico.cern.ch/conferenceDisplay.py?confId=146386
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9<0.94) dsigMC = 0.01;
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9>=0.94) dsigMC = 0.0099;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9<0.94) dsigMC = 0.0217;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9>=0.94) dsigMC = 0.0157;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9<0.94) dsigMC = 0.0326;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9>=0.94) dsigMC = 0.0330;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9<0.94) dsigMC = 0.0331;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9>=0.94) dsigMC = 0.0378;
    } else if (dataset_=="Fall11"||dataset_=="Jan16ReReco") { // values from https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/634.html, consistant with Jan16ReReco corrections
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9<0.94) dsigMC = 0.0096;
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9>=0.94) dsigMC = 0.0074;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9<0.94) dsigMC = 0.0196;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9>=0.94) dsigMC = 0.0141;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9<0.94) dsigMC = 0.0279;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9>=0.94) dsigMC = 0.0268;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9<0.94) dsigMC = 0.0301;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9>=0.94) dsigMC = 0.0293;   
    } else if (dataset_=="Summer12" || dataset_=="ICHEP2012") { 
      // new values from https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/798.html
      // and from https://hypernews.cern.ch/HyperNews/CMS/get/higgs2g/805.html for the EBLowEta
      // averaging over gap and nogap for the EBLowEta case
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9<0.94) dsigMC = 0.0120;
      if (electron.isEB() && fabs(electron.superCluster()->eta())<1 && r9>=0.94) dsigMC = 0.0092;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9<0.94) dsigMC = 0.0222;
      if (electron.isEB() && fabs(electron.superCluster()->eta())>=1 && r9>=0.94) dsigMC = 0.0295;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9<0.94) dsigMC = 0.0334;
      if (electron.isEE() && fabs(electron.superCluster()->eta())<2 && r9>=0.94) dsigMC = 0.0366;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9<0.94) dsigMC = 0.0558;
      if (electron.isEE() && fabs(electron.superCluster()->eta())>=2 && r9>=0.94) dsigMC = 0.0528;   
    }
  
  // now correct the energy
  // intial corrections based on deltaP
  if (!isMC_ && corr!=0.) newEnergy_ = scEnergy/(1+corr);
  // new format
  if (!isMC_ && corr==0.) newEnergy_ = scEnergy*scale;
  // smearing for MC
  if (isMC_) {
    CLHEP::RandGaussQ gaussDistribution(rng->getEngine(), 1.,dsigMC);
    corrMC = gaussDistribution.fire();
    if (debug_) std::cout << "[PatElectronEnergyCalibrator] unsmeared energy " << scEnergy << std::endl;
    newEnergy_ = scEnergy*corrMC;  
    if (debug_) std::cout << "[PatElectronEnergyCalibrator] smeared energy " << newEnergy_ << std::endl;
  }

  // correct energy error for MC and for data as error is obtained from (ideal) MC parametrisation
  if (updateEnergyError_)
   newEnergyError_ = sqrt(newEnergyError_*newEnergyError_ + dsigMC*dsigMC*newEnergy_*newEnergy_) ;
  if (debug_) std::cout << "[PatElectronEnergyCalibrator] ecalEnergy " << electron.ecalEnergy() << " recalibrated ecalEnergy " << newEnergy_ << std::endl;
  if (debug_) std::cout << "[PatElectronEnergyCalibrator] ecalEnergy error " << electron.ecalEnergyError() << " recalibrated ecalEnergy error " << newEnergyError_ << std::endl;

 }


void PatElectronEnergyCalibrator::computeCorrectedMomentumForRegression
( const pat::Electron & electron, int run)
  
{

  double eleMomentum = electron.p();
  double finalMomentum = eleMomentum;
  float corr=0., scale=1.;
  float dsigMC=0., corrMC=0.;

   edm::Service<edm::RandomNumberGenerator> rng;
   if ( ! rng.isAvailable()) {
     throw cms::Exception("Configuration")
       << "XXXXXXX requires the RandomNumberGeneratorService\n"
          "which is not present in the configuration file.  You must add the service\n"
          "in the configuration file or remove the modules that require it.";
   }

   //*************************************************************
   //For regression V01
   //*************************************************************
   if (energyMeasurementType_ == 2) {
     
     // data corrections 
     if (!isMC_) {
       if (dataset_=="Prompt") {
         if (electron.isEB()) {
           if (fabs(electron.superCluster()->eta()) < 1.0) {
             corr = 0.000186;
           } else {
             corr = -0.0092;
           }
         } else {
           corr = -0.0056;
         }
       }
     } 
     else {
       // MC momentum smearing
       if (dataset_=="Summer12" || dataset_=="ICHEP2012") {      
         if (electron.isEB() && fabs(electron.superCluster()->eta()) < 1.0)       dsigMC = 0.0102;
         else if (electron.isEB() && fabs(electron.superCluster()->eta()) >= 1.0) dsigMC = 0.0216;
         else                                                                     dsigMC = 0.0470;
       }
     }
   }

   //*************************************************************
   //For regression V11
   //*************************************************************
   if (energyMeasurementType_ == 4) {
     
     // data corrections 
     if (!isMC_) {
       if (dataset_=="Prompt") {
         if (electron.isEB()) {
           if (fabs(electron.superCluster()->eta()) < 1.0) {
             corr = 0.0007;
           } else {
             corr = -0.0101;
           }
         } else {
           corr = -0.0072;
         }
       }
     }
     else {
       // MC momentum smearing
       if (dataset_== "Summer12" || dataset_== "ICHEP2012") { 
         if (electron.isEB() && fabs(electron.superCluster()->eta()) < 1.0)       dsigMC = 0.0106;
         else if (electron.isEB() && fabs(electron.superCluster()->eta()) >= 1.0) dsigMC = 0.0220;
         else                                                                     dsigMC = 0.0498;
       }
     }
   }

   //define scale from corr
   scale = 1.0 + corr;


   if (!isMC_) {
     //data correction
     finalMomentum = eleMomentum*scale;
   } 
   else {
     //MC smearing
     CLHEP::RandGaussQ gaussDistribution(rng->getEngine(), 1.,dsigMC);
     corrMC = gaussDistribution.fire();
     finalMomentum = eleMomentum*corrMC;
     //std::cout << eleMomentum << " -> " << dsigMC << " :: " << corrMC << " : " << finalMomentum << std::endl;
   }

   math::XYZTLorentzVector oldMomentum = electron.p4() ;
   newMomentum_ = math::XYZTLorentzVector
     ( oldMomentum.x()*finalMomentum/oldMomentum.t(),
       oldMomentum.y()*finalMomentum/oldMomentum.t(),
       oldMomentum.z()*finalMomentum/oldMomentum.t(),
       finalMomentum ) ;

   //keep the errors the same
   errorTrackMomentum_ = electron.trackMomentumError();
   finalMomentumError_ = electron.p4Error(reco::GsfElectron::P4_COMBINATION);

}





void PatElectronEnergyCalibrator::computeEpCombination
 ( pat::Electron & electron )
 {

  //float scEnergy = electron.ecalEnergy() ;
  float scEnergy = newEnergy_ ;
  int elClass = electron.classification() ;

  float trackMomentum  = electron.trackMomentumAtVtx().R() ;
  errorTrackMomentum_ = 999. ;
  
  // retreive momentum error 
  //MultiGaussianState1D qpState(MultiGaussianStateTransform::multiState1D(vtxTsos,0));
  //GaussianSumUtilities1D qpUtils(qpState);
  errorTrackMomentum_ = electron.trackMomentumError();

  float finalMomentum = electron.p4().t(); // initial
  float finalMomentumError = 999.;
  
  // first check for large errors
 
  if (errorTrackMomentum_/trackMomentum > 0.5 && electron.ecalEnergyError()/scEnergy <= 0.5) {
    finalMomentum = scEnergy;    finalMomentumError = electron.ecalEnergyError();
   }
  else if (errorTrackMomentum_/trackMomentum <= 0.5 && electron.ecalEnergyError()/scEnergy > 0.5){
    finalMomentum = trackMomentum;  finalMomentumError = errorTrackMomentum_;
   }
  else if (errorTrackMomentum_/trackMomentum > 0.5 && electron.ecalEnergyError()/scEnergy > 0.5){
    if (errorTrackMomentum_/trackMomentum < electron.ecalEnergyError()/scEnergy) {
      finalMomentum = trackMomentum; finalMomentumError = errorTrackMomentum_;
     }
    else{
      finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError();
     }
  }
  
  // then apply the combination algorithm
  else {

     // calculate E/p and corresponding error
    float eOverP = scEnergy / trackMomentum;
    float errorEOverP = sqrt(
                 (electron.ecalEnergyError()/trackMomentum)*(electron.ecalEnergyError()/trackMomentum) +
                 (scEnergy*errorTrackMomentum_/trackMomentum/trackMomentum)*
                 (scEnergy*errorTrackMomentum_/trackMomentum/trackMomentum));
    //old comb  
//     if ( eOverP  > 1 + 2.5*errorEOverP )
//       {
//  finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError();
//  if ((elClass==reco::GsfElectron::GOLDEN) && electron.isEB() && (eOverP<1.15))
//    {
//      if (scEnergy<15) {finalMomentum = trackMomentum ; finalMomentumError = errorTrackMomentum_;}
//    }
//       }
//     else if ( eOverP < 1 - 2.5*errorEOverP )
//       {
//  finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError();
//  if (elClass==reco::GsfElectron::SHOWERING)
//    {
//      if (electron.isEB())
//        {
//      if(scEnergy<18) {finalMomentum = trackMomentum; finalMomentumError = errorTrackMomentum_;}
//        }
//      else if (electron.isEE())
//        {
//      if(scEnergy<13) {finalMomentum = trackMomentum; finalMomentumError = errorTrackMomentum_;}
//        }
//      else
//        { edm::LogWarning("ElectronMomentumCorrector::correct")<<"nor barrel neither endcap electron ?!" ; }
//    }
//  else if (electron.isGap())
//    {
//      if(scEnergy<60) {finalMomentum = trackMomentum; finalMomentumError = errorTrackMomentum_;}
//    }
//       }
//     else 
//       {
//  // combination
//  finalMomentum = (scEnergy/electron.ecalEnergyError()/electron.ecalEnergyError() + trackMomentum/errorTrackMomentum_/errorTrackMomentum_) /
//    (1/electron.ecalEnergyError()/electron.ecalEnergyError() + 1/errorTrackMomentum_/errorTrackMomentum_);
//  float finalMomentumVariance = 1 / (1/electron.ecalEnergyError()/electron.ecalEnergyError() + 1/errorTrackMomentum_/errorTrackMomentum_);
//  finalMomentumError = sqrt(finalMomentumVariance);
//       }
//   }
    
//new comb

    bool eleIsNotInCombination = false ;
     if ( (eOverP  > 1 + 2.5*errorEOverP) || (eOverP  < 1 - 2.5*errorEOverP) || (eOverP < 0.8) || (eOverP > 1.3) )
      { eleIsNotInCombination = true ; }
     if (eleIsNotInCombination)
      {
       if (eOverP > 1)
        { finalMomentum = scEnergy ; finalMomentumError = electron.ecalEnergyError() ; }
       else
        {
         if (elClass == reco::GsfElectron::GOLDEN)
          { finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError(); }
         if (elClass == reco::GsfElectron::BIGBREM)
          {
           if (scEnergy<36)
            { finalMomentum = trackMomentum ; finalMomentumError = errorTrackMomentum_ ; }
           else
            { finalMomentum = scEnergy ; finalMomentumError = electron.ecalEnergyError() ; }
          }
         if (elClass == reco::GsfElectron::BADTRACK)
          { finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError() ; }
         if (elClass == reco::GsfElectron::SHOWERING)
          {
           if (scEnergy<30)
            { finalMomentum = trackMomentum ; finalMomentumError = errorTrackMomentum_; }
           else
            { finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError();}
          }
         if (elClass == reco::GsfElectron::GAP)
          {
           if (scEnergy<60)
            { finalMomentum = trackMomentum ; finalMomentumError = errorTrackMomentum_ ; }
           else
            { finalMomentum = scEnergy; finalMomentumError = electron.ecalEnergyError() ; }
          }
        }
      }
 
     else
      {
       // combination
       finalMomentum = (scEnergy/electron.ecalEnergyError()/electron.ecalEnergyError() + trackMomentum/errorTrackMomentum_/errorTrackMomentum_) /
         (1/electron.ecalEnergyError()/electron.ecalEnergyError() + 1/errorTrackMomentum_/errorTrackMomentum_);
       float finalMomentumVariance = 1 / (1/electron.ecalEnergyError()/electron.ecalEnergyError() + 1/errorTrackMomentum_/errorTrackMomentum_);
       finalMomentumError = sqrt(finalMomentumVariance);
      }
  } 


  
// }
  
  math::XYZTLorentzVector oldMomentum = electron.p4() ;
  newMomentum_ = math::XYZTLorentzVector
   ( oldMomentum.x()*finalMomentum/oldMomentum.t(),
     oldMomentum.y()*finalMomentum/oldMomentum.t(),
     oldMomentum.z()*finalMomentum/oldMomentum.t(),
     finalMomentum ) ;
  finalMomentumError_ =  finalMomentumError;  
  //if (debug_) std::cout << "[ElectronEnergCorrector] old comb momentum " << oldMomentum.t() << " new comb momentum " << newMomentum_.t() << std::endl;

 }
