#include "kNN.hpp"

void tc1()
{
  Dataset dataset;
  dataset.loadFromCSV("mnist.csv");
  int nRows, nCols;

  kNN knn;
  Dataset X_train, X_test, y_train, y_test;
  Dataset feature = dataset.extract(0, -1, 1, -1);
  Dataset label = dataset.extract(0, -1, 0, 0);

  train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
  knn.fit(X_train, y_train);
  Dataset y_pred = knn.predict(X_test);

  cout << "y_pred" << endl;
  y_pred.printHead(10, 10);
  cout << endl;
  cout << "y_test" << endl;
  y_test.printHead(10, 10);
  cout << endl;

  double accuracy = knn.score(y_test, y_pred);
  cout << "Accuracy: " << accuracy << endl;
}

void tc()
{
  int nRows, nCols;
  Dataset dataset;
  dataset.loadFromCSV("mnist.csv");
  Dataset dataset2 = Dataset(dataset);
  bool result = dataset2.drop(1, 0, "label");
  cout << "Drop(1, \"label\") result: " << result << endl;
}

int main()
{

  tc1();
  return 0;
}