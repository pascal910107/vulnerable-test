/**
 * @name Infinite Loop Detection
 * @description 檢查可能因條件判斷不當而導致無限迴圈的情形。
 * @kind problem
 * @id cpp/infinite-loop
 * @tags security
 */
import cpp

from WhileStmt whileStmt
where whileStmt.getCondition().toString() = "true"
select whileStmt, "請確認該無限迴圈是否有適當的跳出機制，以避免死循環。"
