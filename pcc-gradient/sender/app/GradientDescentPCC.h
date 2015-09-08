#ifndef __GRADIENT_DESCENT_PCC_H__
#define __GRADIENT_DESCENT_PCC_H__

#include "pcc.h"

class GradientDescentPCC: public PCC {
public:
	GradientDescentPCC() : PCC(6, true), first_(true), up_utility_(0), down_utility_(0), consecutive_big_changes_(0) {}

protected:
/*
	virtual void init() {
		PCC::init();
		first_ = true;
		up_utility_ = 0;
		down_utility_ = 0;
		consecutive_big_changes_ = 0;
	}
*/

	virtual void search() {
		guess();
	}
	virtual void decide(long double curr_utility) {
		/*if (conditions_changed_too_much_){
			consecutive_big_changes_++;
			return;
		}*/
		consecutive_big_changes_ = 0;

		double high = 0, low = 0;
		for (int i = 0; i < kHistorySize / 2; i++) {
			high += search_monitor_utility[i];
		}
		for (int i = kHistorySize/2; i < kHistorySize; i++) {
			low += search_monitor_utility[i];
		}


		double gradient = (high/10 - low/10) / (2 * kDelta);
		double change = kEpsilon * gradient;
		double ratio = 1 + change / base_rate_;
		if (ratio > 1.05) {
			base_rate_ *= 1.05;
		} else if (ratio < 0.95) {
			base_rate_ *= 0.95;
		} else {
			base_rate_ += change;
		}
		if (base_rate_ < kDelta) {
			base_rate_ = kDelta;
		}
	}

private:
	void guess() {
		if (first_) {
			if (search_number < kHistorySize - 1) base_rate_ = rate();
			if (search_number == kHistorySize - 1) first_ = false;
		}
		if (search_number < kHistorySize / 2) {
			setRate(base_rate_ + kDelta);
		} else {
			setRate(base_rate_ - kDelta);
		}

	}
	void adapt() {
	}

	bool first_;
	double base_rate_;
	double up_utility_;
	double down_utility_;
	size_t consecutive_big_changes_;

	static const double kEpsilon = 0.002;
	static const double kDelta = 0.0125;//0.7;

};

#endif
