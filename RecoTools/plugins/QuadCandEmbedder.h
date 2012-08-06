/*  ---------------------
File: QuadCandEmbedder
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Embed some information about 4l out->at(i)idates (angles, cross-leg inv. mass, etc.)
*/

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TLorentzVector.h"


template <class T>
class QuadCandEmbedder : public edm::EDProducer {
    public:
        explicit QuadCandEmbedder(const edm::ParameterSet& iConfig){
            src_ = iConfig.getParameter<edm::InputTag>("src");
            minMll_ = iConfig.getParameter<double>("minMll");
            produces<std::vector<T> >();
            }

        ~QuadCandEmbedder() {}


    private:
        virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            using namespace edm;
            using namespace reco;

            std::vector<T> toBeSorted;
            Handle<std::vector<T> > cands;
            if(iEvent.getByLabel(src_,cands)) 
                toBeSorted =  *cands;

            std::auto_ptr<std::vector<T> > out(new std::vector<T>);
            for(unsigned int i=0;i<toBeSorted.size();++i){
                out->push_back(toBeSorted.at(i));
            }
            for (unsigned int i = 0; i < out->size(); ++i) {
                double costheta1=-137.0; double costheta2=-137.0; double phi=-137.0; double costhetastar=-137.0; double phistar1=-137.0; double phistar2=-137.0; double phistar12=-137.0; double phi1=-137.0; double phi2=-137.0;

                TLorentzVector HP4 = convertToTLorentz(out->at(i).p4());
                TLorentzVector z1P4 = convertToTLorentz(out->at(i).leg1()->p4());
                TLorentzVector z1l1P4 = convertToTLorentz(out->at(i).leg1()->leg1()->p4());
                TLorentzVector z1l2P4 = convertToTLorentz(out->at(i).leg1()->leg2()->p4());
                TLorentzVector z2P4 = convertToTLorentz(out->at(i).leg2()->p4());
                TLorentzVector z2l1P4 = convertToTLorentz(out->at(i).leg2()->leg1()->p4());
                TLorentzVector z2l2P4 = convertToTLorentz(out->at(i).leg2()->leg2()->p4());

                TLorentzVector temp;
                if (out->at(i).leg1()->leg1()->charge() >0 ){ //make sure angles are calculated wrt negative lepton
                    temp=z1l1P4;
                    z1l1P4=z1l2P4;
                    z1l2P4=temp;
                }
                if (out->at(i).leg2()->leg1()->charge() >0 ){
                    temp=z2l1P4;
                    z2l1P4=z2l2P4;
                    z2l2P4=temp;
                }

                bool fourFour = false;
                bool sixSix = false;

                int charge11 = out->at(i).leg1()->leg1()->charge();
                int charge12 = out->at(i).leg1()->leg2()->charge();
                int charge21 = out->at(i).leg2()->leg1()->charge();
                int charge22 = out->at(i).leg2()->leg2()->charge();

                bool check11=false;
                bool check12=false;

                if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg1()->leg2()->p4())).M() > minMll_){
                    if (((out->at(i).leg2()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_){

                        //check OS combinations between legs
                        if (charge11!=charge21){
                            if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_) check11=true;
                        } else if (charge11!=charge22){
                            if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_) check11=true;
                        }

                        if (charge12!=charge21){
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_) check12=true;
                        } else if (charge12!=charge22){
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_) check12=true;
                        }
                        if (check11 && check12) {
                            fourFour=true;
                        }
                    }
                }

                if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg1()->leg2()->p4())).M() > minMll_)
                    if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_)
                        if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_)
                                if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                                    if (((out->at(i).leg2()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                                        sixSix=true;

                calculateAngles(HP4, z1P4, z1l1P4, z1l2P4, z2P4, z2l1P4, z2l2P4, costheta1, costheta2, phi, costhetastar, phistar1, phistar2, phistar12, phi1, phi2);
                out->at(i).setAngles(costheta1, costheta2, phi, costhetastar, phistar1, phistar2, phistar12, phi1, phi2);
                out->at(i).setNoFSRMass((out->at(i).leg1()->noPhoP4()+out->at(i).leg2()->noPhoP4()).M());
                out->at(i).setInvMasses(out->at(i).leg1()->leg1()->p4(),out->at(i).leg1()->leg2()->p4(),out->at(i).leg2()->leg1()->p4(),out->at(i).leg2()->leg2()->p4(),fourFour,sixSix);
            }
            iEvent.put(out);

        } 

        TLorentzVector convertToTLorentz(const reco::Candidate::LorentzVector& lorV){
            TLorentzVector out;
            out.SetPxPyPzE( lorV.px(), lorV.py(), lorV.pz(), lorV.energy() );
            return out;
        }

        void calculateAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4Lep11, TLorentzVector thep4Lep12, TLorentzVector thep4Z2, TLorentzVector thep4Lep21, TLorentzVector thep4Lep22, double& costheta1, double& costheta2, double& phi, double& costhetastar, double& phistar1, double& phistar2, double& phistar12, double& phi1, double& phi2){
            //std::cout << "In calculate angles..." << std::endl;

            double norm;

            TVector3 boostX = -(thep4H.BoostVector());
            TLorentzVector thep4Z1inXFrame( thep4Z1 );
            TLorentzVector thep4Z2inXFrame( thep4Z2 );  
            thep4Z1inXFrame.Boost( boostX );
            thep4Z2inXFrame.Boost( boostX );
            TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
            TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );

            // calculate phi1, phi2, costhetastar
            phi1 = theZ1X_p3.Phi();
            phi2 = theZ2X_p3.Phi();

            ///////////////////////////////////////////////
            // check for z1/z2 convention, redefine all 4 vectors with convention
            /////////////////////////////////////////////// 
            TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;

            /* old convention of choosing Z1 ------------------------------
               p4H = thep4H;
               if ((phi1 < 0)&&(phi1 >= -TMath::Pi())){
               p4Z1 = thep4Z2; p4M11 = thep4Lep21; p4M12 = thep4Lep22;
               p4Z2 = thep4Z1; p4M21 = thep4Lep11; p4M22 = thep4Lep12;     
               costhetastar = theZ2X_p3.CosTheta();
               }
               else{
               p4Z1 = thep4Z1; p4M11 = thep4Lep11; p4M12 = thep4Lep12;
               p4Z2 = thep4Z2; p4M21 = thep4Lep21; p4M22 = thep4Lep22;
               costhetastar = theZ1X_p3.CosTheta();
               } ---------------------------------------------- */

            p4Z1 = thep4Z1; p4M11 = thep4Lep11; p4M12 = thep4Lep12;
            p4Z2 = thep4Z2; p4M21 = thep4Lep21; p4M22 = thep4Lep22;
            costhetastar = theZ1X_p3.CosTheta();

            //std::cout << "phi1: " << phi1 << ", phi2: " << phi2 << std::endl;

            // now helicity angles................................
            // ...................................................
            TVector3 boostZ1 = -(p4Z1.BoostVector());
            TLorentzVector p4Z2Z1(p4Z2);
            p4Z2Z1.Boost(boostZ1);
            //find the decay axis
            /////TVector3 unitx_1 = -Hep3Vector(p4Z2Z1);
            TVector3 unitx_1( -p4Z2Z1.X(), -p4Z2Z1.Y(), -p4Z2Z1.Z() );
            norm = 1/(unitx_1.Mag());
            unitx_1*=norm;
            //boost daughters of z2
            TLorentzVector p4M21Z1(p4M21);
            TLorentzVector p4M22Z1(p4M22);
            p4M21Z1.Boost(boostZ1);
            p4M22Z1.Boost(boostZ1);
            //create z and y axes
            /////TVector3 unitz_1 = Hep3Vector(p4M21Z1).cross(Hep3Vector(p4M22Z1));
            TVector3 p4M21Z1_p3( p4M21Z1.X(), p4M21Z1.Y(), p4M21Z1.Z() );
            TVector3 p4M22Z1_p3( p4M22Z1.X(), p4M22Z1.Y(), p4M22Z1.Z() );
            TVector3 unitz_1 = p4M21Z1_p3.Cross( p4M22Z1_p3 );
            norm = 1/(unitz_1.Mag());
            unitz_1 *= norm;
            TVector3 unity_1 = unitz_1.Cross(unitx_1);

            //caculate theta1
            TLorentzVector p4M11Z1(p4M11);
            p4M11Z1.Boost(boostZ1);
            TVector3 p3M11( p4M11Z1.X(), p4M11Z1.Y(), p4M11Z1.Z() );
            TVector3 unitM11 = p3M11.Unit();
            double x_m11 = unitM11.Dot(unitx_1); double y_m11 = unitM11.Dot(unity_1); double z_m11 = unitM11.Dot(unitz_1);
            TVector3 M11_Z1frame(y_m11, z_m11, x_m11);
            costheta1 = M11_Z1frame.CosTheta();
            //std::cout << "theta1: " << M11_Z1frame.Theta() << std::endl;
            //////-----------------------old way of calculating phi---------------/////////
            phi = M11_Z1frame.Phi();

            //set axes for other system
            TVector3 boostZ2 = -(p4Z2.BoostVector());
            TLorentzVector p4Z1Z2(p4Z1);
            p4Z1Z2.Boost(boostZ2);
            TVector3 unitx_2( -p4Z1Z2.X(), -p4Z1Z2.Y(), -p4Z1Z2.Z() );
            norm = 1/(unitx_2.Mag());
            unitx_2*=norm;
            //boost daughters of z2
            TLorentzVector p4M11Z2(p4M11);
            TLorentzVector p4M12Z2(p4M12);
            p4M11Z2.Boost(boostZ2);
            p4M12Z2.Boost(boostZ2);
            TVector3 p4M11Z2_p3( p4M11Z2.X(), p4M11Z2.Y(), p4M11Z2.Z() );
            TVector3 p4M12Z2_p3( p4M12Z2.X(), p4M12Z2.Y(), p4M12Z2.Z() );
            TVector3 unitz_2 = p4M11Z2_p3.Cross( p4M12Z2_p3 );
            norm = 1/(unitz_2.Mag());
            unitz_2*=norm;
            TVector3 unity_2 = unitz_2.Cross(unitx_2);
            //calcuate theta2
            TLorentzVector p4M21Z2(p4M21);
            p4M21Z2.Boost(boostZ2);
            TVector3 p3M21( p4M21Z2.X(), p4M21Z2.Y(), p4M21Z2.Z() );
            TVector3 unitM21 = p3M21.Unit();
            double x_m21 = unitM21.Dot(unitx_2); double y_m21 = unitM21.Dot(unity_2); double z_m21 = unitM21.Dot(unitz_2);
            TVector3 M21_Z2frame(y_m21, z_m21, x_m21);
            costheta2 = M21_Z2frame.CosTheta();

            // calculate phi
            //calculating phi_n
            TLorentzVector n_p4Z1inXFrame( p4Z1 );
            TLorentzVector n_p4M11inXFrame( p4M11 );
            n_p4Z1inXFrame.Boost( boostX );
            n_p4M11inXFrame.Boost( boostX );        
            TVector3 n_p4Z1inXFrame_unit = n_p4Z1inXFrame.Vect().Unit();
            TVector3 n_p4M11inXFrame_unit = n_p4M11inXFrame.Vect().Unit();  
            TVector3 n_unitz_1( n_p4Z1inXFrame_unit );
            //// y-axis is defined by neg lepton cross z-axis
            //// the subtle part is here...
            //////////TVector3 n_unity_1 = n_p4M11inXFrame_unit.Cross( n_unitz_1 );
            TVector3 n_unity_1 = n_unitz_1.Cross( n_p4M11inXFrame_unit );
            TVector3 n_unitx_1 = n_unity_1.Cross( n_unitz_1 );

            TLorentzVector n_p4M21inXFrame( p4M21 );
            n_p4M21inXFrame.Boost( boostX );
            TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();
            //rotate into other plane
            TVector3 n_p4M21inXFrame_unitprime( n_p4M21inXFrame_unit.Dot(n_unitx_1), n_p4M21inXFrame_unit.Dot(n_unity_1), n_p4M21inXFrame_unit.Dot(n_unitz_1) );

            ///////-----------------new way of calculating phi-----------------///////
            //double phi_n =  n_p4M21inXFrame_unitprime.Phi();
            /// and then calculate phistar1
            TVector3 n_p4PartoninXFrame_unit( 0.0, 0.0, 1.0 );
            TVector3 n_p4PartoninXFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_1), n_p4PartoninXFrame_unit.Dot(n_unity_1), n_p4PartoninXFrame_unit.Dot(n_unitz_1) );
            // negative sign is for arrow convention in paper
            phistar1 = (n_p4PartoninXFrame_unitprime.Phi());

            // and the calculate phistar2
            TLorentzVector n_p4Z2inXFrame( p4Z2 );
            n_p4Z2inXFrame.Boost( boostX );
            TVector3 n_p4Z2inXFrame_unit = n_p4Z2inXFrame.Vect().Unit();
            ///////TLorentzVector n_p4M21inXFrame( p4M21 );
            //////n_p4M21inXFrame.Boost( boostX );        
            ////TVector3 n_p4M21inXFrame_unit = n_p4M21inXFrame.Vect().Unit();  
            TVector3 n_unitz_2( n_p4Z2inXFrame_unit );
            //// y-axis is defined by neg lepton cross z-axis
            //// the subtle part is here...
            //////TVector3 n_unity_2 = n_p4M21inXFrame_unit.Cross( n_unitz_2 );
            TVector3 n_unity_2 = n_unitz_2.Cross( n_p4M21inXFrame_unit );
            TVector3 n_unitx_2 = n_unity_2.Cross( n_unitz_2 );
            TVector3 n_p4PartoninZ2PlaneFrame_unitprime( n_p4PartoninXFrame_unit.Dot(n_unitx_2), n_p4PartoninXFrame_unit.Dot(n_unity_2), n_p4PartoninXFrame_unit.Dot(n_unitz_2) );
            phistar2 = (n_p4PartoninZ2PlaneFrame_unitprime.Phi());

            double phistar12_0 = phistar1 + phistar2;
            if (phistar12_0 > TMath::Pi()) phistar12 = phistar12_0 - 2*TMath::Pi();
            else if (phistar12_0 < (-1.)*TMath::Pi()) phistar12 = phistar12_0 + 2*TMath::Pi();
            else phistar12 = phistar12_0;

        }

        // ----------member data ---------------------------
        edm::InputTag src_;
        double minMll_;



};
