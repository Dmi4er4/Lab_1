### Асимптотика
Для поиска кратчайших маршрутов между вершинами использовались разные алгоритмы, т.к. асимптотически для графов разных структур  подходили более специфические подходы. 

В частности, для графа в общем виде с _m_ ребрами и _n_ вершинами был написан алгоритм Дейкстры с кучей.  Его асимптотическая сложность равна `O(m*log(n))`:
``` c++
distance[from] = 0;
  std::priority_queue<Path, std::vector<Path>, std::greater<>> sorted_paths;
  sorted_paths.push(Path(distance[from], from));

  while (!sorted_paths.empty()) {
    Path current_path = sorted_paths.top();
    sorted_paths.pop();
    int vertex = current_path.to;

    if (distance[vertex] != current_path.length) {
      continue;
    }

    if (vertex == to) {
      std::vector<Edge> result;
      int current_location = to;

      while (current_location != from) {
        result.emplace_back(current_location,
                            previous[current_location].length);
        current_location = previous[current_location].to;
      }

      std::reverse(result.begin(), result.end());
      return result;
    }

    for (Edge edge: connections_[vertex]) {
      if (distance[edge.to] > distance[vertex] + edge.length) {
        distance[edge.to] = distance[vertex] + edge.length;
        previous[edge.to] = Edge(vertex, edge.length);
        sorted_paths.push(Path(distance[edge.to], edge.to));
      }
    }
  }
```

Для полного графа асимптотически быстрее представлялся алгоритм Дейкстры без использования кучи, ведь его асимптотика оценивается в`O(m+ n²)`,  что выгоднее для клики с _n_ вершинами и _&frac12;*(n&sup2;+n)_ ребрами:
``` c++
distance[from] = 0;
  std::priority_queue<Clique::Path, std::vector<Path>, std::greater<>>
      sorted_paths;
  sorted_paths.push(Path(distance[from], from));

  while (!sorted_paths.empty()) {
    Path current_path = sorted_paths.top();
    sorted_paths.pop();
    int vertex = current_path.to;

    if (distance[vertex] != current_path.length) {
      continue;
    }

    if (vertex == to) {
      std::vector<Edge> result;
      int current_location = to;

      while (current_location != from) {
        result.emplace_back(current_location,
                            previous[current_location].length);
        current_location = previous[current_location].to;
      }

      std::reverse(result.begin(), result.end());
      return result;
    }
    for (int i = 0; i < n_; i++) {
      if (i == vertex) {
        continue;
      }
      if (distance[i] > distance[vertex] + connection_matrix_[vertex][i]) {
        distance[i] = distance[vertex] + connection_matrix_[vertex][i];
        previous[i] = Edge(vertex, connection_matrix_[vertex][i]);
        sorted_paths.push(Path(distance[i], i));
      }
    }
  }
```

А для графа-цепи достаточно было осуществить обход по существующим путям с асимптотикой `O(n)`:
``` c++
while (from != to && from != -1) {
    result.push_back(connections_[from]);
    from = connections_[from].to;
  }
```
Для оптимизации метода `TrafficManager::Transport` был использован метод _GetShortestPaths_ . Таким образом не пришлось вызывать _GetShortestPath_ для каждой вершины, а обойдясь одним вызовом алгоритма Дейкстры получилось соптимизировать асимптотику до `O(n²)`,  которая достигается из-за необходимости в худшем случае обойти _n_ раз все _n_ вершин в возвращаемых путях.
### Методы анализа

Для анализирования эффективности работы кода был использован встроенный в gcc механизм `std::chrono`.  Написанные в [time_research.cpp](https://github.com/Dmi4er4/Lab_1/blob/time/time_research.cpp) тесты позволяют оценить время работы написанного решения на графах разной структуры, с разными размерами и с разным количеством итераций выполнения этих тестов.

Для более разнообразных данных также было принято решение замерить время на графах, созданных от int по правилам, описанных в условиях лабораторной работы и на графах, созданных из случайных ребер.

Точка начала и конца транспортировки, а также количество транспортируемых булочек также выбирались случайно для большей достоверности данных.

### Статистика

Удобнее всего представить полученные результаты в виде сборной таблицы.

50.000 итераций:

Graph type \ Size|Graph, int constructor| Clique, int constructor |Chain, int constructor| Random Graph| Random Clique| Random Chain
------------- | ------------- | ------------- | ------------- | ------------- | -------------| -------------
__10__  |6228 ms | 8855 ms| 3260 ms| 8510 ms |7214 ms | 3298 ms
__20__  |12609 ms | 12381 ms| 7931 ms| 18762 ms|15624 ms| 8140 ms
__50__  |31507 ms | 37947 ms| 27297 ms| 64078 ms| 54581 ms | 27475 ms
__100__  | 82631 ms| 116936 ms| 75376 ms| 16625 ms|158091 ms| 77598 ms
__200__  | 253202 ms| 403966 ms| 224467 ms |475492  ms | 502495 ms| 228376 ms

100.000 итераций:

Graph type \ Size|Graph, int constructor| Clique, int constructor |Chain, int constructor| Random Graph| Random Clique| Random Chain
------------- | ------------- | ------------- | ------------- | ------------- | -------------| -------------
__10__  |12243 ms |12912 ms|6470 ms|16870 ms |14491 ms |6464  ms
__20__  |23988 ms |238872 ms| 15593 ms|38012 ms|31946 ms|15809 ms
__50__  |66172 ms| 77046ms| 54115 ms|121525 ms|106213 ms |54174 ms
__100__  |171827 ms|232903 ms| 151060 ms|337797 ms|317772 ms|151318 ms
__200__  |527290 ms|856526 ms| 501864 ms |968842  ms |1080861  ms|460758 ms

### Анализ

+ Для начала стоит заметить, что в большинстве случаев время, полученное после 100.000 итераций, равно удвоенному эквиваленту с 50.000 итераций. Это означает, что решение работает стабильно, а тесты охватывают достаточную область входных данных, чтобы утверждать об их достоверности.

+ Также видно, что _Graph_ и  _Clique_ отрабатывает быстрее на своих версиях с конструктором от int, чем на их случайных эквивалентах. Это не удивительно, так как асимптотика не всегда показывает реальное время и в краевых случаях (коим является и граф с единичными весами на ребрах) алгоритм может отрабатывать намного быстрее, чем на случайных входных данных.

+ _Chain_ же работает примерно одинаковое количество времени из-за меньшего простора в разнообразии создаваемого графа и, как следствие, более предсказуемом времени работы без особых краевых случаев.

+ К тому же можно заметить, что в версии с конструктором от int _Clique_ отрабатывает в среднем медленнее, чем _Graph_, в отличие от случайных версий. Это сведетельствует о том, что предпочтение, данное алгоритму Дейкстры без использования кучи для  _Clique_ имеет смысл в среднем, но может проигрывать в краевых случаях.

+ Еще интересным наблюдением является почти двоекратное увеличение времени работы _Graph_, чего не замечено за _Clique_. Это происходит из-за гигантского различия структуры случайного графа от полного, который производит конструктор от int. Клика же не настолько изменяет свою форму, оттого и различия во времени меньше.
