#pragma once

struct playerStats
{
    int guess_games_played = 0;
    int total_guesses = 0;
    int optimal_guesses_sum = 0;
    double total_guess_effeciency = 0.0;

    int ttt_games_played = 0;
    int ttt_wins = 0;
    int ttt_draws = 0;
    int ttt_losses = 0;
    int ttt_missed_wins = 0;
    double ttt_total_points = 0.0;

    int connect4_games_played = 0;
    int connect4_wins = 0;
    int connect4_draws = 0;
    int connect4_losses = 0;
    int connect4_missed_wins = 0;
    double connect4_total_points = 0.0;

    double total_focus_games_effeciency = 0.0;
    double total_focus_games_missed_wins = 0;

    int chess_games_played = 0;
    int chess_wins = 0;
    int chess_losses = 0;
    int chess_draws = 0;
    double chess_total_think_time = 0.0;
    int chess_total_moves_made = 0;
    double chess_avg_time_per_move = 0.0;
    int chess_total_material_balance = 0;
    double chess_avg_material_advantage = 0.0;
    double chess_total_score = 0.0;

    int checkers_games_played = 0;
    int checkers_wins = 0;
    int checkers_losses = 0;
    double checkers_total_think_time = 0.0;
    int checkers_total_captures = 0;
    int checkers_total_moves_made = 0;
    double checkers_avg_time_per_move = 0.0;
    int checkers_total_material_balance = 0;
    double checkers_avg_material_advantage = 0.0;
    double checkers_total_score = 0.0;

    double strategy_total_score = 0.0;
    double strategy_think_time = 0.0;

    int hangman_games_played = 0;
    int hangman_wins = 0;
    int hangman_losses = 0;
    int hangman_total_difficulty_attempted = 0;
    int hangman_total_wrong_guesses = 0;
    double hangman_total_score = 0.0;
};

void draw_bar(double score);
std::string get_comment(std::string category, double score, double strategyTime, int focusMissedWins);
void print_final_report(playerStats &stats);
void update_guess_stats(playerStats &stats, int guessesTaken, int currentRange);
void update_ttt_stats(playerStats &stats, int result, int missed_wins);
void update_connect4_stats(playerStats &stats, int result, int missed_wins);
void update_focus_games_stats(playerStats &stats);
void update_chess_stats(playerStats &stats, int result, double think_time, int moves_made, int material_balance);
void update_checkers_stats(playerStats &stats, int result, double think_time, int moves_made, int captures_made, int material_balance);
void update_strategy_stats(playerStats &stats);
void update_hangman_stats(playerStats &stats, int result, int difficulty_attempted, int wrong_guesses);