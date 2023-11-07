//MultiViewData.cpp - main function for the multi-view data

#include <vector>
//other includes

int main() {
    std::vector<double> inputData;
    int ret = 0;

    // Add code

    if (ret == 0) {
        // Generate some random data and make predictions, five times
        const int TRIALS = 5;
        for (int i = 0; i < TRIALS; ++i) {
            const int NUM = 1000;
            for (int j = 0; j < NUM; ++j) {
                inputData.push_back((double)(rand() % 1000) / 1000);//generate a number between 0 and 1
            }
            // Make a prediction using the trained model and display it in all views

            //clear out the vector for the next trial
            inputData.clear();
            std::cout << std::endl;
        }
    }

    // Add code

    return ret;
}