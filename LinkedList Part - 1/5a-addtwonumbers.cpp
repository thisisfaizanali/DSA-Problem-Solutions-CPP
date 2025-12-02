/*++++++++++++++++++++++++++++++++++++++++++++++++++++++  Bismillah  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Bruteforce solution :
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *temp = l1;
        vector<int> a, b, c;
        while (temp)
        {
            // 2 4 3
            a.push_back(temp->val);
            temp = temp->next;
        }
        reverse(a.begin(), a.end()); // 3 4 2
        temp = l2;
        while (temp)
        {
            // 5 6 4
            b.push_back(temp->val);
            temp = temp->next;
        }
        reverse(b.begin(), b.end()); // 4 6 5

        int i = a.size() - 1, j = b.size() - 1, carry = 0;
        // we add from the back so start with units place which is at size - 1 index :
        while (i >= 0 || j >= 0 || carry)
        {
            int sum = carry;
            if (i >= 0)
                sum += a[i--];
            if (j >= 0)
                sum += b[j--];
            c.push_back(sum % 10);
            carry = sum / 10;
        }

        // construct the list :
        ListNode *head = new ListNode(c[0]);
        ListNode *curr = head;
        for (int k = 1; k < c.size(); ++k)
        {
            curr->next = new ListNode(c[k]);
            curr = curr->next;
        }
        return head;
    }
};

// Optimal Solution :
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        // my brute solution memory limit was exceeded
        // whenever you have to generate a new list
        //  use a dummy node
        int carry = 0;
        ListNode *dummyNode = new ListNode();
        // for creation of new nodes, i used temp
        ListNode *temp = dummyNode;
        while (l1 != NULL || l2 != NULL || carry)
        // can use a separate if condition for carry
        // outside the while loop if carry> 0
        // make a new node and do the thing
        {
            int sum = 0;
            if (l1 != NULL)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            ListNode *newNode = new ListNode(sum % 10);
            temp->next = newNode;
            temp = temp->next;
        }
        return dummyNode->next;
    }
};