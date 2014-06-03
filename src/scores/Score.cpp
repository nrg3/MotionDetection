#include "Score.h"

Score::Score () 
		: true_positives_(0), false_positives_(0)
		, true_negatives_(0), false_negatives_(0) {
}

Score::Score (int true_positives, int false_positives, int true_negatives, int false_negatives)
		: true_positives_(true_positives), false_positives_(false_positives)
		, true_negatives_(true_negatives), false_negatives_(false_negatives) {
}

long double Score::get_recall() const {
	return static_cast<long double> (true_positives_) / (true_positives_ + false_positives_);
}

long double Score::get_precision() const {
	return static_cast<long double> (true_positives_) / (true_positives_ + false_negatives_);
}
long double Score::get_f_score() const {
	long double precision = get_precision();
	long double recall = get_recall();
	return 2 * precision * recall / (precision + recall);
}

vector<long double> Score::get_scores() const {
	vector<long double> scores;
	scores.push_back(get_recall());
	scores.push_back(get_precision());
	scores.push_back(get_f_score());
	return scores;
}