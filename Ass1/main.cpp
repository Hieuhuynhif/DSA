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

void tc1126()
{
  Dataset dataset;
  dataset.loadFromCSV("mnist.csv");
  dataset.printTail();
  dataset.printTail();
}

void tc1143()
{
  int nRows, nCols;
  Dataset dataset;
  dataset.loadFromCSV("mnist.csv");
  bool result = dataset.drop(0, 0);
  cout << "Drop(0,0) result: " << result;
}

int main()
{
  // tc1();

  tc1143();
  return 0;
}