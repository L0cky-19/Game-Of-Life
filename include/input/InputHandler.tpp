#include "InputHandler.hpp"
#include <iostream>
#include <algorithm>
#include <type_traits>

template <typename T>
T InputHandler::handleInput(const string& question, const T& defaultValue, vector<T> validResponses, inputType inputType) {
    T response;
    bool validInput = false;

    do {
        cout << question;
        string input;
        getline(cin, input);

        // Trim l'input
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Vérifier si l'input est vide ou ne contient que des espaces
        if (input.empty() || input.find_first_not_of(" \t") == string::npos) {
            cout << "Input cannot be empty. Please try again.\n";
            continue;  // Retourne au début de la boucle
        }

        try {
            // Validation spécifique selon le type d'input
            if constexpr (std::is_same_v<T, string>) {
                if (inputType == inputType::inputFilename) {
                    // Vérification que le fichier n'est pas que des espaces
                    if (input.find_first_not_of(" \t") == string::npos) {
                        throw runtime_error("Filename cannot be empty or only whitespace");
                    }
                    response = input;
                    validInput = true;
                }
                else {
                    // Pour les autres inputs string, vérifier si la réponse est valide
                    if (!validResponses.empty() &&
                        find(validResponses.begin(), validResponses.end(), input) == validResponses.end()) {
                        throw runtime_error("Invalid input. Please choose from the available options.");
                    }
                    response = input;
                    validInput = true;
                }
            }
            else if constexpr (std::is_same_v<T, int>) {
                // Vérifier que l'input ne contient que des chiffres
                if (input.find_first_not_of("0123456789") != string::npos) {
                    throw runtime_error("Please enter only numbers");
                }

                int value = std::stoi(input);

                // Validation spécifique selon le type d'input
                if (inputType == inputType::inputGridDataWidth) {
                    if (value < 1 || value > 300) {
                        throw runtime_error("Grid dimensions must be between 1 and 300");
                    }
                }
                else if (inputType == inputType::inputGridDataHeight) {
                    if (value < 1 || value > 300) {
                        throw runtime_error("Grid dimensions must be between 1 and 300");
                    }
                }
                else if (inputType == inputType::inputIterationNumber) {
                    if (value < 1 || value > 1000000) {
                        throw runtime_error("Value must be between 1 and 1000000");
                    }
                }
                else if (inputType == inputType::inputIterationDelay) {
                    if (value < 0 || value > 1000000) {
                        throw runtime_error("Value must be between 0 and 1000000 (ms)");
                    }
                }

                response = value;
                validInput = true;
            }
            else if constexpr (std::is_same_v<T, bool>) {
                if (input != "y" && input != "n" && input != "Y" && input != "N") {
                    throw runtime_error("Please enter y or n");
                }
                response = (input == "y" || input == "Y");
                validInput = true;
            }
        }
        catch (const exception& e) {
            cout << e.what() << "\n";
        }
    } while (!validInput);

    return response;
}
