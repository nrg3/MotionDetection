#ifndef SCORE__SCORE_H
#define SCORE__SCORE_H

#include <vector>
using std::vector;

class Score {
private:
	// the number of foreground pixels correctly detected
	int true_positives_;
	// the number of background pixels incorrectly detected as foreground
	int false_positives_;
	//the number of background pixels correctly detected
	int true_negatives_;
	// the number of foreground pixels incorrectly detected as background
	int false_negatives_;
public:
	Score ();
	Score (int true_positives, int false_positives, int true_negatives, int false_negatives);

	// different metrics
	long double get_recall() const;
	long double get_precision() const;
	long double get_f_score() const;

	vector<long double> get_scores() const;
};

#endif