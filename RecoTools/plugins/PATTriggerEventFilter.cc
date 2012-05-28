/*
 * =====================================================================================
 *
 *       Filename:  TriggerEventFilter.cc
 *
 *    Description:  Filter events by string cut on a PAT Trigger event
 *
 *         Author:  Evan Friis, evan.friis@cern.ch
 *        Company:  UW Madison
 *
 * =====================================================================================
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/RegexMatch.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

#include <boost/regex.hpp>

class TriggerEventFilter : public edm::EDFilter {
	public:
		TriggerEventFilter(const edm::ParameterSet& pset);
		virtual ~TriggerEventFilter(){}
		bool filter(edm::Event& evt, const edm::EventSetup& es);
	private:
		edm::InputTag src_;
		std::vector<std::string> paths_;
		StringCutObjectSelector<pat::TriggerEvent> cut_;
};

TriggerEventFilter::TriggerEventFilter(const edm::ParameterSet& pset):
	src_ (pset.getParameter<edm::InputTag>("src")),
	paths_ (pset.getParameter<std::vector<std::string> >("paths")),
	cut_ (pset.getParameter<std::string>("cut"), true) { }

	bool TriggerEventFilter::filter(edm::Event& evt, const edm::EventSetup& es) {
		edm::Handle<pat::TriggerEvent> trgevt;
		//		std::cout << trgEvent << std::endl;
		evt.getByLabel(src_, trgevt);
		const pat::TriggerEvent& result=(*trgevt);
		const pat::TriggerPathCollection* paths = result.paths();
		bool pass=false;
		std::string pattern="";
		for (unsigned int j=0; j<paths->size(); ++j){
			for (unsigned int i = 0; i < paths_.size(); ++i) {
				pattern = edm::glob2reg(paths_.at(i)+"*");
				boost::regex matcher(pattern);
				if (boost::regex_match(paths->at(j).name(), matcher)) {
//					std::cout << "Match found! " << paths->at(j).name() << " matches " << matcher << std::endl;
//					std::cout << "Did it fire? " << paths->at(j).wasAccept() << std::endl;
					if (paths->at(j).wasAccept()) return true;
				}
			}
			//			std::cout << "Does it exist?: " << (*trgevt).pathRef(paths_.at(i)).isNonnull() << std::endl;
		}
		return pass;
	}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TriggerEventFilter);
