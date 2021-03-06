/*
  Copyright Christopher Cooper and Kristofer Rye 2013

  This file is part of scoutify-merger.

  scoutify-merger is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  scoutify-merger is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with scoutify-merger.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MATCH_H
#define MATCH_H

#include <src/fields.h>

#define  AUTON_WEIGHT 1.3
#define  TRUSS_WEIGHT 0.8
#define  CATCH_WEIGHT 2.0
#define ASSIST_WEIGHT 1.5
#define   HIGH_WEIGHT 0.7
#define    LOW_WEIGHT 2.0

typedef struct match {
	/* team is implied because the match should be withing a team struct */
	position_t position;

	char round[16];

	// note: for now we are disregarding event, we may add that functionality in the future,
	// but it can't hurt to have it in the form.

	auto_shot_t auto_shot;
	bool auto_hot;
	bool auto_mobility;
	int high_goals_scored;
	int high_goals_attempted;
	int low_goals_scored;
	int low_goals_attempted;
	int trusses_scored;
	int trusses_attempted;
	int catches_scored;
	int catches_attempted;
	int passes_scored;
	int passes_attempted;
	int receives_scored;
	int receives_attempted;
	int blocks_scored;
	int blocks_attempted;

	char notes[65536];
} match_t;

match_t *match_new();
match_t *match_new_from_data(position_t position,
                             char round[16],
                             auto_shot_t auto_shot,
                             bool auto_hot,
                             bool auto_mobility,
                             int high_goals_scored,
                             int high_goals_attempted,
                             int low_goals_scored,
                             int low_goals_attempted,
                             int trusses_scored,
                             int trusses_attempted,
                             int catches_scored,
                             int catches_attempted,
                             int passes_scored,
                             int passes_attempted,
                             int receives_scored,
                             int receives_attempted,
                             int blocks_scored,
                             int blocks_attempted,
                             char notes[65536]);
int match_set_from_data(match_t *in,
                        position_t position,
                        char round[16],
                        auto_shot_t auto_shot,
                        bool auto_hot,
                        bool auto_mobility,
                        int high_goals_scored,
                        int high_goals_attempted,
                        int low_goals_scored,
                        int low_goals_attempted,
                        int trusses_scored,
                        int trusses_attempted,
                        int catches_scored,
                        int catches_attempted,
                        int passes_scored,
                        int passes_attempted,
                        int receives_scored,
                        int receives_attempted,
                        int blocks_scored,
                        int blocks_attempted,
                        char notes[65536]);

int match_free();

int print_match(match_t *match);

int match_get_team_score(match_t *match);
int match_get_team_value(match_t *match);

#endif
