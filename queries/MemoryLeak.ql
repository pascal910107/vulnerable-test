/**
 * @name Memory Leak Detection
 * @description 檢查 new 分配後未有對應 delete 的情形。
 * @kind problem
 * @id cpp/memory-leak
 * @tags security
 */
import cpp

from Expr newExpr
where newExpr.toString().regexpMatch("new\\s+\\w+")
select newExpr, "檢查 new 分配的記憶體是否有相對應的釋放(delete)。"
