#include <iostream>
#include <iomanip>
#include <cmath>
#include "Stats.h"
#include "Utilities.h"
using namespace std;

// Function that draws bars according to the score
void draw_bar(double score)
{
    int bars = (int)(score / 5); // 100% = 20 bars
    if (bars > 20)
        bars = 20;

    cout << " [";
    // Darws green, yellow or red bars depending on the score
    if (score >= 75)
        cout << GREEN;
    else if (score >= 40)
        cout << YELLOW;
    else
        cout << RED;
    for (int i = 0; i < bars; i++)
        cout << "|";
    cout << RESET;
    for (int i = bars; i < 20; i++)
        cout << ".";
    cout << "] " << (int)score << "%";
}

// Gets comment to display depending on score and other data
string get_comment(string category, double score, double strategyTime = 0.0, int focusMissedWins = 0)
{
    if (category == "LOGIC")
    {
        if (score >= 75)
            return "Binary Search Detected. You are thinking like a computer (Halving the range)";
        if (score >= 50)
            return "Heuristic Approach. You have a strategy, but it's not fully optimized.";
        if (score == 0)
            return "No Data.";
        return "Random Walk. You are guessing blindly instead of narrowing the search space";
    }
    else if (category == "FOCUS")
    {
        // If they missed more than 2 winning moves, this is the main problem to flag.
        if (focusMissedWins > 2)
        {
            return "Tunnel Vision. You are missing guaranteed wins right in front of you.";
        }

        // 2. High Performance
        if (score >= 75)
        {
            return "Eagle Eye. Perfect board awareness; you exploit every gap.";
        }

        // 3. Medium Performance
        else if (score >= 40)
        {
            if (focusMissedWins > 0)
                return "Drifting. You play well, but you let a few opportunities slip.";
            else
                return "Solid Focus. You see the board well, but you need sharper tactics.";
        }

        else if (score == 0)
            return "No data.";

        // 4. Low Performance
        else
        {
            // We already caught the "High Missed Wins" case at the top. So this player is paying attention but still losing.
            return "Outmaneuvered. You are attentive, but your opponent is trapping you.";
        }
    }
    // Also uses how long it took user to play next move to display a personalized message
    else if (category == "STRATEGY")
    {
        // High Performance
        if (score >= 75)
        {
            if (strategyTime < 17.0)
                return "Intuitive Tactician. You spot winning lines quickly.";
            else
                return "Grandmaster Style. You take your time and convert advantages efficiently.";
        }

        // Medium Performance
        else if (score >= 40)
        {
            if (strategyTime < 17.0)
                return "Rapid Mover. Good instincts, but try slowing down to find better trades.";
            else
                return "Methodical. You play a solid, safe game.";
        }

        else if (score == 0)
            return "No data.";

        // Low Performance
        else
        {
            if (strategyTime < 17.0)
                return "Impulsive Blitzer. You are playing too fast! Slow down and check for traps.";
            else
                return "Over-Thinker. You spend a lot of time thinking but still lose material.";
        }
    }
    else if (category == "VOCABULARY")
    {
        if (score >= 75)
            return "Lexicon Elite. You handle rare patterns easily.";
        if (score >= 50)
            return "Proficient. Good with common words.";
        if (score == 0)
            return "No Data.";
        return "Guesswork. You struggle with structure.";
    }
    return "";
}

void print_final_report(playerStats &stats)
{
    cout << "=================================================" << endl
         << "       C O G N I T I V E   P R O F I L E         " << endl
         << "=================================================" << endl;

    cout << "USER: Player_01" << endl
         << endl;

    cout << left << setw(25) << "LOGIC (Efficiency):";
    draw_bar(stats.total_guess_effeciency);
    cout << endl
         << get_comment("LOGIC", stats.total_guess_effeciency) << endl
         << endl
         << endl;

    cout << left << setw(25) << "VOCABULARY:";
    draw_bar(stats.hangman_total_score);
    cout << endl
         << get_comment("VOCABULARY", stats.hangman_total_score) << endl
         << endl
         << endl;

    cout << left << setw(25) << "FOCUS (Attention):";
    draw_bar(stats.total_focus_games_effeciency);
    cout << endl
         << get_comment("FOCUS", stats.total_focus_games_effeciency, 0, stats.total_focus_games_missed_wins) << endl
         << endl
         << endl;

    cout << left << setw(25) << "STRATEGY:";
    draw_bar(stats.strategy_total_score);
    cout << endl
         << get_comment("STRATEGY", stats.strategy_total_score, stats.strategy_think_time) << endl
         << endl
         << endl;

    cout << "-------------------------------------------------" << endl;

    // FIND STRONGEST & WEAKEST
    double scores[4] = {stats.total_guess_effeciency, stats.hangman_total_score, stats.total_focus_games_effeciency, stats.strategy_total_score};

    int maxIndex = 0;
    double maxVal = scores[0];
    for (int i = 1; i < 4; i++)
    {
        if (scores[i] > maxVal)
        {
            maxVal = scores[i];
            maxIndex = i;
        }
    }

    int minIndex = 0;
    double minVal = scores[0];
    for (int i = 1; i < 4; i++)
    {
        if (scores[i] < minVal && scores[i] > 0)
        {
            minVal = scores[i];
            minIndex = i;
        }
    }

    string conclusion = "Rookie. Keep practicing to build your profile.";
    if (maxVal >= 60)
    {
        // GENERATE CONCLUSION
        switch (maxIndex)
        {
        case 0: // High Logic
            conclusion = "Your Algorithmic Efficiency is your strongest asset. You minimize waste.";
            break;
        case 1: // High Focus
            conclusion = "Your Linguistic Aptitude is dominant. You handle complex patterns easily.";

            break;
        case 2: // High Strategy
            conclusion = "Your Error Rate is exceptionally low. You maintain high consistency.";

            break;
        case 3: // High Verbal
            conclusion = "Your Tactical Foresight is exceptional. You consistently outmaneuver opponents.";

            break;
        }
    }

    // GENERATE RECOMMENDATION
    string recommendation = "None. Good consistency across all games.";
    if (minVal < 50)
    {
        switch (minIndex)
        {
        case 0: // Low Logic
            recommendation = "Adopt a 'Divide and Conquer' search strategy (Binary Search) to improve efficiency.";
            break;
        case 1: // Low Focus
            recommendation = "Vocabulary risk tolerance is low. Attempt higher-difficulty words to maximize score.";

            break;
        case 2: // Low Strategy
            recommendation = "High rate of unforced errors detected. Validate opponent threats before moving.";
            break;
        case 3: // Low Verbal
            recommendation = "Defensive consistency is low. Always verify that your target square is safe before moving.";
            break;
        }
    }

    cout << "ANALYSIS SUMMARY" << endl;
    cout << "Primary Strength:    " << conclusion << endl;
    cout << "Area for Improvement: " << recommendation << endl;

    cout << "=================================================" << endl;

    pauseScreen();
}

// Update the stats data of Guess the Number game
void update_guess_stats(playerStats &stats, int guessesTaken, int currentRange)
{
    stats.guess_games_played++;
    stats.total_guesses += guessesTaken;

    int perfectScore = (int)ceil(log2(currentRange));
    stats.optimal_guesses_sum += perfectScore;

    stats.total_guess_effeciency = (static_cast<double>(stats.optimal_guesses_sum) / stats.total_guesses) * 100;
    if (stats.total_guess_effeciency > 100)
        stats.total_guess_effeciency = 100;
}

// Update the stats data of Tic Tac Toe
void update_ttt_stats(playerStats &stats, int result, int missed_wins)
{
    stats.ttt_games_played++;

    if (result == 0)
        stats.ttt_draws++;
    else if (result == 1)
        stats.ttt_wins++;
    else if (result == -1)
        stats.ttt_losses++;

    stats.ttt_missed_wins += missed_wins;

    stats.ttt_total_points = (stats.ttt_draws * 0.7) + (stats.ttt_wins * 1.0) - (stats.ttt_missed_wins * 0.3);
    update_focus_games_stats(stats);
}

// Update the stats data of Connect 4
void update_connect4_stats(playerStats &stats, int result, int missed_wins)
{
    stats.connect4_games_played++;

    if (result == 0)
        stats.connect4_draws++;
    else if (result == 1)
        stats.connect4_wins++;
    else if (result == -1)
        stats.connect4_losses++;

    stats.connect4_missed_wins += missed_wins;

    stats.connect4_total_points = 1.1 * ((stats.connect4_draws * 0.5) + (stats.connect4_wins * 1.0) - (stats.connect4_missed_wins * 0.3));
    update_focus_games_stats(stats);
}

// Combine the stats of Tic Tac Toe and Connect 4
void update_focus_games_stats(playerStats &stats)
{
    stats.total_focus_games_effeciency = ((stats.ttt_total_points + stats.connect4_total_points) / (stats.ttt_games_played + stats.connect4_games_played)) * 100;
    if (stats.total_focus_games_effeciency > 100)
        stats.total_focus_games_effeciency = 100;

    stats.total_focus_games_missed_wins = (static_cast<double>(stats.ttt_missed_wins + stats.connect4_missed_wins)) / (stats.ttt_games_played + stats.connect4_games_played);
}

// Update the stats data of chess
void update_chess_stats(playerStats &stats, int result, double think_time, int moves_made, int material_balance)
{
    stats.chess_games_played++;

    if (result == 1)
        stats.chess_wins++;
    else if (result == -1)
        stats.chess_losses++;
    else if (result == 0)
        stats.chess_draws++;

    stats.chess_total_think_time += think_time;
    stats.chess_total_moves_made += moves_made;
    stats.chess_total_material_balance += material_balance;

    stats.chess_avg_time_per_move = stats.chess_total_think_time / stats.chess_total_moves_made;
    stats.chess_avg_material_advantage = stats.chess_total_material_balance / stats.chess_games_played;
    stats.chess_total_score = static_cast<double>((stats.chess_wins * 70) + (stats.chess_draws * 35) + (stats.chess_avg_material_advantage * 2));

    update_strategy_stats(stats);
}

// Update the stats data of checkers
void update_checkers_stats(playerStats &stats, int result, double think_time, int moves_made, int captures_made, int material_balance)
{
    stats.checkers_games_played++;

    if (result == 1)
        stats.checkers_wins++;
    else if (result == -1)
        stats.checkers_losses++;

    stats.checkers_total_think_time += think_time;
    stats.checkers_total_moves_made += moves_made;
    stats.checkers_total_captures += captures_made;
    stats.checkers_total_material_balance += material_balance;

    stats.checkers_avg_time_per_move = stats.checkers_total_think_time / stats.checkers_total_moves_made;
    stats.checkers_avg_material_advantage = stats.checkers_total_material_balance / stats.checkers_games_played;
    stats.checkers_total_score = static_cast<double>((stats.checkers_wins * 70) + (stats.checkers_avg_material_advantage * 5));

    update_strategy_stats(stats);
}

// Combine the stats of chess and checkers
void update_strategy_stats(playerStats &stats)
{
    stats.strategy_total_score = (stats.chess_total_score + stats.checkers_total_score) / (stats.chess_games_played + stats.checkers_games_played);
    if (stats.strategy_total_score > 100)
        stats.strategy_total_score = 100;

    stats.strategy_think_time = (stats.chess_total_think_time + stats.checkers_total_think_time) / (stats.chess_total_moves_made + stats.checkers_total_moves_made);
}

// Update the stats of hangman
void update_hangman_stats(playerStats &stats, int result, int difficulty_attempted, int wrong_guesses)
{
    stats.hangman_games_played++;

    if (result == 1)
        stats.hangman_wins++;
    else if (result == -1)
        stats.hangman_losses++;

    stats.hangman_total_difficulty_attempted += difficulty_attempted;
    stats.hangman_total_wrong_guesses += wrong_guesses;

    stats.hangman_total_score = (static_cast<double>(stats.hangman_total_difficulty_attempted) / (stats.hangman_total_wrong_guesses + 1)) * 25;
    if (stats.hangman_total_score > 100)
        stats.hangman_total_score = 100;
}