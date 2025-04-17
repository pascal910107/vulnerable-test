/**
 * @name Logical Error Detection
 * @description 檢查 if 條件是否為常數，可能導致邏輯錯誤。
 * @kind problem
 * @id cpp/logical-error
 * @tags security
 */
import cpp

from IfStmt stmt
where stmt.getCondition().toString().regexpMatch("^(true|false)$")
select stmt, "檢查此 if 條件是否正確，避免因硬編碼常數導致邏輯錯誤。"
