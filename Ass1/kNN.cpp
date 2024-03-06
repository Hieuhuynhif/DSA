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
    }
    else if (index == count - 1)
    {
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
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
    Node *temp = head;
    while (temp)
    {
        cout << temp->data;
        if (temp->next)
            cout << " ";
        temp = temp->next;
    }
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
Dataset::~Dataset()
{
    delete data;
};
Dataset::Dataset(const Dataset &other)
{
    data = other.data;
};

Dataset &Dataset::operator=(const Dataset &other)
{
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
        if (i + 1 != nColsLabel)
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
            if (i + 1 != cols)
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
    // if(label) nCols++;
};
void Dataset::columns() const
{
    label->print();
};
bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis != 0 || axis != 1)
        return false;

    if (axis == 0)
    {
        if (index < 0 || index > data->length())
            return false;

        data->remove(index);
    }
    if (axis == 1)
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
    return true;
};
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset extract;

    if (startRow == 0)
    {
        int colLabel = endCol;
        List<string> *newLabel = new DLinkedList<string>();
        if (endCol == -1)
            colLabel = label->length()-1;
            
        for (int i = startCol; i <= colLabel; i++)
        {
            newLabel->push_back(label->get(i));
        }
        extract.setLabel(newLabel);
    }

    if (endRow == -1)
        endRow = data->length();

    for (int i = startRow; i < endRow; i++)
    {
        List<int> *row = new DLinkedList<int>();
        int col = endCol;
        if (endCol == -1)
            col = data->get(i)->length()-1;
        for (int j = startCol; j <= col; j++)
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
    return X_test;
};
double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    return 0.05;
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test){};
