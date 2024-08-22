#ifndef NN_HPP_INCLUDED
#define NN_HPP_INCLUDED

#include <Features/Matrix/Matrix.hpp>

#include <vector>

enum ActivationType { SIGMOID };

class NeuralNetwork {
    public:
        NeuralNetwork(const int nb_entries=2);
        ~NeuralNetwork();

        void addLayer(const int nb_neuron, const ActivationType type = SIGMOID);
        void clear(void);
        void setEntriesNumber(const int nb_entries);
        void train(const Matrix& X_train, const Matrix& Y_train, const int epoch=1, const float learning_rate=1.0f);
        void predict(const Matrix& X_train, const Matrix& Y_train);
        void show(void);

    private:
        std::vector<ActivationType> l_activationFunc;
        std::vector<Matrix> l_weight;
        std::vector<Matrix> l_bias;

        int m_nb_entries;
};

#endif