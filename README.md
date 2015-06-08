# n-puzzle-solver-with-CV

###Cmake

OpenCV dir point to : `opencv/build/`

###Known Issue
 * ~~`generateGoalState()` have bugz~~
 * ~~只接受 `2x2` 之puzzle~~
 * 每個 `tile` 嚴格限制 `150*150 pixels`
 * 只接受一個空格
 * 空格必須全白
 * `goal state`左上角不能是空格
 * `Segmenting()` 中判斷空格有誤差
 * 建關係時，有可能有 loop
 * ~~移動之後再按`Solve It!!!`會當掉~~
