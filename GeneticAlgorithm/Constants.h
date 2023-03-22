#pragma once
#include <string>

//CFileReadingException
const std::string AT_PAIR = " at pair: ";
const std::string WHILE_READING_FILE = ", while reading file: ";

//CIncorrectValueException
const std::string MUST_BE_GREATER_THAN_INFO = " must be greater than: ";
const std::string MUST_BE_LOWER_THAN_INFO = " must be lower than: ";
const std::string MUST_BE_BETWEEN_INFO = " must be between: ";
const std::string CANNOT_BE_NEGATIVE_INFO = " cannot be negative";
const std::string AND = " and ";

//CIncorrectProbabilityException
const std::string INCORRECT_PROBABILITY_INFO = "probability";

//CKnapsackProblem
const std::string INCORRECT_CAPACITY_OF_KNAPSACK_INFO = "Knapsack capacitymust be a number and " + MUST_BE_GREATER_THAN_INFO + "0";
const std::string INCORRECT_ITEMS_AMOUNT_INFO = "Item amount must be an integer and " + MUST_BE_GREATER_THAN_INFO + "0";
const std::string INCORRECT_SET_SIZE_INFO = "Values and weights set size" + MUST_BE_GREATER_THAN_INFO + "0";
const std::string INCORRECT_VALUES_OF_ITEMS_INFO = "Negative value of item";
const std::string INCORRECT_WEIGHTS_OF_ITEMS_INFO = "Negative weight of item";
const std::string INCORRECT_NUMBER_OF_ITEMS_INFO = "Incorrect number of items";
const std::string INCORRECT_TYPE_INFO = "There is a incorrect type";
const std::string FILE_NOT_FOUND_INFO = "File could not be found: ";

//CIndividual
const std::string INCORRECT_GENOTYPE_SIZE_INFO = "Size of genotype";

//CGeneticAlgorithm
const std::string NULLPTR_PROBLEM_INFO = "Problem cannot be a nullptr!";
const std::string NOT_ENOUGH_INDIVIDUALS_INFO = "Population size";
const std::string INCORRECT_STOP_CONDITION_INFO = "Stop condition cannot";
const std::string INCORRECT_BREEDING_PARTAKERS_AMOUNT_INFO = "Amount of breeding partakers";
const std::string BREEDING_PROBABILITY = "Breeding ";
const std::string MUTATION_PROBABILITY = "Mutation ";