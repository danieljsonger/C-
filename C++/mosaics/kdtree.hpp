/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] == second[curDim]) { return first < second; }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    int best = 0;
    int pot = 0;

    for (int i = 0; i < Dim; i++){
        best += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
        pot += (target[i] - potential[i]) * (target[i] - potential[i]);
    }

    if (pot == best) { return potential < currentBest; }

    return pot < best;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> Points = newPoints;
    traverse(0, newPoints.size() - 1, Points, 0, root);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = _copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  delete this;

  root = _copy(rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _destructor(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> nearest = root->point;
    traverseNearest(query, nearest, 0, root);
    return nearest;
}

template <int Dim>
int KDTree<Dim>::distance(const Point<Dim> &first,
                          const Point<Dim> &second) const
{
    unsigned int dist = 0;
    for (int i = 0; i < Dim; i++)
    {
        dist += (first[i] - second[i]) * (first[i] - second[i]);
    }
    return dist;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(KDTreeNode * other)
{ 
  if (other) {
      KDTreeNode * n = new KDTreeNode();
      n->point = other->point;
      n->left = _copy(other->left);
      n->right = _copy(other->right);
      return n;
  }
  return NULL;
}

template <int Dim>
void KDTree<Dim>::_destructor(KDTreeNode * subRoot){
    if(subRoot){
        _destructor(subRoot->left);
        _destructor(subRoot->right);
        delete subRoot;
    }
}

template <int Dim>
void KDTree<Dim>::traverseNearest(const Point<Dim> &query, Point<Dim> &best, int dim, KDTreeNode *current) const
{
    bool goL = false;
    bool goR = false;
    bool replace = false;

    if (current->left && smallerDimVal(query, current->point, dim)) {
        traverseNearest(query, best, (dim + 1) % Dim, current->left);
        goL = true;
    }

    if (current->right && !smallerDimVal(query, current->point, dim)) {
        traverseNearest(query, best, (dim + 1) % Dim, current->right);
        goR = true;
    }

    if (shouldReplace(query, best, current->point)) {
        best = current->point;
        replace = true;
    }

    if (goL) {
        if (current->right) {
          if ((query[dim] - current->point[dim]) * (query[dim] - current->point[dim]) <= distance(query, best)){
            traverseNearest(query, best, (dim + 1) % Dim, current->right);
          }
        }
    }

    if (goR) {
      if (current->left) {
        if ((query[dim] - current->point[dim]) * (query[dim] - current->point[dim]) <= distance(query, best)) {
          traverseNearest(query, best, (dim + 1) % Dim, current->left);
        }
      }
    }
}

template <int Dim>
void KDTree<Dim>::swap(int index1, int index2, vector<Point<Dim>> &newPoints)
{
    Point<Dim> temp = newPoints[index1];
    newPoints[index1] = newPoints[index2];
    newPoints[index2] = temp;
}

template <int Dim>
void KDTree<Dim>::partition(int left, int right, int pivot, vector<Point<Dim>> &newPoints, int dim)
{
    for (int i = left; i < right; i++)
    {
        for (int j = left; j < right; j++)
        {
            if (smallerDimVal(newPoints[j + 1], newPoints[j], dim))
            {
                swap(j + 1, j, newPoints);
            }
        }
    }
}

template <int Dim>
void KDTree<Dim>::traverse(int left, int right, vector<Point<Dim>> &newPoints, int dim, KDTreeNode *&node)
{
    if (left > right)
    {
        node = NULL;
        return;
    }
    int pivot = (right + left) / 2;
    partition(left, right, pivot, newPoints, dim);
    KDTreeNode * newN = new KDTreeNode();
    newN->point = newPoints[pivot];
    node = newN;
    traverse(left, pivot - 1, newPoints, (dim + 1) % Dim, newN->left);
    traverse(pivot + 1, right, newPoints, (dim + 1) % Dim, newN->right);
}
