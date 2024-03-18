#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

template <typename T>
DLinkedList<T>::DLinkedList()
{
    head = tail = nullptr;
    count = 0;
}

template <typename T>
DLinkedList<T>::~DLinkedList()
{
    this->clear();
    delete head;
    delete tail;
}

template <typename T>
void DLinkedList<T>::push_back(T value)
{
    if (count == 0)
    {
        head = tail = new Node(value);
        count++;
    }
    else
    {
        tail->next = new Node(value);
        tail->next->prev = tail;
        tail = tail->next;
        count++;
    }
};

template <typename T>
void DLinkedList<T>::push_front(T value)
{
    if (count == 0)
    {
        head = tail = new Node(value);
        count++;
    }
    else
    {
        head->prev = new Node(value);
        head->prev->next = head;
        head = head->prev;
        count++;
    }
};

template <typename T>
void DLinkedList<T>::insert(int index, T value)
{
    if (index < 0 || index > count)
        return;
    else if (index == 0)
        this->push_front(value);
    else if (index == count)
        this->push_back(value);
    else
    {
        Node *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        temp->prev->next = new Node(value);
        temp->prev->next->prev = temp->prev;
        temp->prev->next->next = temp;
        temp->prev = temp->prev->next;
        count++;
    }
};

template <typename T>
void DLinkedList<T>::remove(int index)
{
    if (index < 0 || index > count)
        return;
    else if (index == 0)
    {
        Node *temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        count--;
    }
    else if (index == count - 1)
    {
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        count--;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        count--;
    }
};

template <typename T>
T &DLinkedList<T>::get(int index) const
{
    if (index < 0 || index > count)
        throw std::out_of_range("get(): Out of range");

    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
};

template <typename T>
int DLinkedList<T>::length() const
{
    return count;
}

template <typename T>
void DLinkedList<T>::clear()
{
    Node *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    count = 0;
};

template <typename T>
void DLinkedList<T>::print() const
{
    if (count == 0)
        cout << "";
    Node *temp = head;
    while (temp)
    {
        cout << temp->data;
        // if (temp->next)
        cout << " ";
        temp = temp->next;
    }
    cout << endl;
};

template <typename T>
void DLinkedList<T>::reverse()
{
    Node *temp = head;
    Node *change;
    while (temp)
    {
        temp->next = change;
        temp->next = temp->prev;
        temp->prev = change;

        temp = temp->next;
    }
    head = temp;
    head = tail;
    tail = temp;
};

Dataset::Dataset()
{
    data = new DLinkedList<List<int> *>();
    label = new DLinkedList<string>();
};
Dataset::~Dataset(){
    // delete data;
    // delete label;
};
Dataset::Dataset(const Dataset &other)
{
    data = other.data;
    label = other.label;
};

Dataset &Dataset::operator=(const Dataset &other)
{
    delete data;
    delete label;
    data = other.data;
    label = other.label;
    return *this;
};
bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream file;
    file.open(fileName);
    if (!file)
        return false;
    string line;
    getline(file, line);

    stringstream ss(line);
    string temp;
    while (getline(ss, temp, ','))
    {
        label->push_back(temp);
    }

    while (getline(file, line))
    {
        List<int> *newList = new DLinkedList<int>();
        stringstream ss(line);

        int number;
        while (getline(ss, temp, ','))
        {
            stringstream(temp) >> number;
            newList->push_back(number);
        }

        data->push_back(newList);
    }
    file.close();

    return true;
};
void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
        return;
    int nColsLabel = nCols;
    if (nCols > label->length())
        nColsLabel = label->length();

    for (int i = 0; i < nColsLabel; i++)
    {
        cout << label->get(i);
        if (i + 1 != nColsLabel)
            cout << " ";
    }
    cout << endl;

    List<int> *row;
    int rows = nRows;
    if (nRows > data->length())
        rows = data->length();
    for (int i = 0; i < rows; i++)
    {
        row = data->get(i);
        int cols = nCols;
        if (nCols > row->length())
            cols = row->length();
        for (int i = 0; i < cols; i++)
        {
            cout << row->get(i);
            if (i + 1 != cols)
                cout << " ";
        }
        if (i + 1 != rows)
            cout << endl;
    }
}
void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
        return;
    List<int> *row;
    int nColsLabel = nCols;
    if (nCols > label->length())
        nColsLabel = label->length();

    for (int i = label->length() - nColsLabel; i < label->length(); i++)
    {
        cout << label->get(i);
        if (i + 1 != label->length())
            cout << " ";
    }

    cout << endl;

    int rows = nRows;
    if (nRows > data->length())
        rows = data->length();
    for (int i = data->length() - rows; i < data->length(); i++)
    {
        row = data->get(i);
        int cols = nCols;
        if (nCols > row->length())
            cols = row->length();
        for (int i = row->length() - cols; i < row->length(); i++)
        {
            cout << row->get(i);
            if (i + 1 != row->length())
                cout << " ";
        }
        if (i + 1 != data->length())
            cout << endl;
    }
};
void Dataset::getShape(int &nRows, int &nCols) const
{
    nRows = data->length();
    nCols = 0;
    List<int> *row;
    for (int i = 0; i < data->length(); i++)
    {
        row = data->get(i);
        if (row->length() > nCols)
            nCols = row->length();
    }
};
void Dataset::columns() const
{
    label->print();
};
bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis != 0 && axis != 1)
        return false;

    else if (axis == 0)
    {
        if (index < 0 || index >= data->length())
            return false;

        data->remove(index);
        return true;
    }

    else
    {
        for (int i = 0; i < data->length(); i++)
        {
            if (label->get(i) == columns)
            {
                int index = i;
                for (int i = 0; i < data->length(); i++)
                {
                    data->get(i)->remove(index);
                }
                return true;
            }
        }
        return false;
    }
};
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset extract;

    List<string> *newLabel = new DLinkedList<string>();
    if (endCol == -1)
        endCol = label->length() - 1;
    if (endRow == -1)
        endRow = data->length();

    for (int i = startCol; i <= endCol; i++)
    {
        newLabel->push_back(label->get(i));
    }
    extract.setLabel(newLabel);

    for (int i = startRow; i < endRow; i++)
    {
        List<int> *row = new DLinkedList<int>();

        for (int j = startCol; j <= endCol; j++)
        {
            row->push_back(data->get(i)->get(j));
        }
        extract.pushRow(row);
    }
    return extract;
};
List<List<int> *> *Dataset::getData() const
{
    return data;
};
void Dataset::pushRow(List<int> *row)
{
    data->push_back(row);
}
void Dataset::setLabel(List<string> *&newLabel)
{
    label = newLabel;
};

kNN::kNN(int k)
{
    this->k = k;
};

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    xTrain = X_train;
    yTrain = y_train;
};

Dataset kNN::predict(const Dataset &X_test)
{
    Dataset y_pred;
    List<string> *label = new DLinkedList<string>();

    label->push_back("label");
    y_pred.setLabel(label);
    for (int i = 0; i < X_test.getData()->length(); i++)
    {
        List<int> *testRow = X_test.getData()->get(i);
        List<int> *row = new DLinkedList<int>();
        int lenTrain = xTrain.getData()->length();
        int labels[lenTrain];

        for (int i = 0; i < yTrain.getData()->length(); i++)
        {
            labels[i] = yTrain.getData()->get(i)->get(0);
        }
        double distances[lenTrain];
        int index = 0;

        for (int j = 0; j < xTrain.getData()->length(); j++)
        {
            List<int> *trainRow = xTrain.getData()->get(j);
            double distance = 0.0;
            for (int m = 0; m < testRow->length(); m++)
            {
                distance = distance + pow((testRow->get(m) - trainRow->get(m)), 2);
            }

            distances[index] = sqrt(distance);
            index++;
        }

        for (int i = 0; i < k; i++)
        {
            for (int j = index - 1; j > i; j--)
            {
                if (distances[j - 1] > distances[j])
                {
                    double temp = distances[j];
                    distances[j] = distances[j - 1];
                    distances[j - 1] = temp;

                    int label = labels[j];
                    labels[j] = labels[j - 1];
                    labels[j - 1] = label;
                }
            }
        }

        int element;
        int max = 0;
        for (int i = 0; i < k; i++)
        {
            int counter = 0;
            for (int j = i; j < k; j++)
            {
                if (labels[j] == labels[i])
                    counter++;
            }
            if (counter > max || (counter == max && labels[i] < element))
            {
                max = counter;
                element = labels[i];
            }
        }
        row->push_back(element);
        y_pred.pushRow(row);
    }

    return y_pred;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    int hit = 0;
    for (int i = 0; i < y_test.getData()->length(); i++)
    {
        if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0))
            hit++;
    }
    double accuracy = (hit * 1.0) / y_test.getData()->length();

    return accuracy;
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int nRows, nCols;
    X.getShape(nRows, nCols);
    int rows = nRows * (1 - test_size);
    X_train = X.extract(0, rows, 0, -1);
    y_train = y.extract(0, rows, 0, -1);
    X_test = X.extract(rows, -1, 0, -1);
    y_test = y.extract(rows, -1, 0, -1);
};
