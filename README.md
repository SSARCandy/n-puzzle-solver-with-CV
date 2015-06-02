# n-puzzle-solver-with-CV

###Cmake

OpenCV dir point to : `opencv/build/`

###Known Issue
 * 每個 `tile` 嚴格限制 `150*150 pixels`
 * 只接受 `2x2` 之puzzle
 * 只接受一個空格
 * 空格必須全白
 * `start state`, `goal state`左上角皆不能是空格
 * `generateGoalState()` have bugz
 * `Segmenting()` 中判斷空格有誤差
 * 建關係時，有可能有 loop
