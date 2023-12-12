#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <iostream>

int* Dijkstra(int matrix[][100],int source,int vertex_num)
{
	bool visited[100];
	static int  dist[100];
    int  path[100];
    for(int i=0;i<100;i++)
	{
		visited[i]=false;
		path[i]=source;
    }
    visited[source] = true;
    for (int i = 0; i < vertex_num; i++)
    {
        dist[i] = matrix[source][i];
        path[i] = source;
    }

    
    int min_cost;        // Ȩֵ��С
    int min_cost_index;  // Ȩֵ��С���±�

    for (int i = 1; i < vertex_num; i++)  // �ҵ�Դ�㵽���� vertex_num-1 ��������·��
    {
        min_cost = 2147483647;
		
        for (int j = 0; j < vertex_num; j++)
        {
            if (visited[j] == false && dist[j] < min_cost)  // �ҵ�Ȩֵ��С
            {
                min_cost = dist[j];
                min_cost_index = j;
            }
        }
        
			visited[min_cost_index] = true;  // �õ����ҵ������б��

        for (int j = 0; j < vertex_num; j++)  // ���� dist ����
        {
            if (visited[j] == false && min_cost != 2147483647 &&
                matrix[min_cost_index][j] != 2147483647 &&  // ȷ������֮���б�
                matrix[min_cost_index][j] + min_cost < dist[j])
            {
                dist[j] = matrix[min_cost_index][j] + min_cost;
                path[j] = min_cost_index;
            }
        }

    }
    return dist;
}

#endif