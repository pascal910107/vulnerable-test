/**
 * @name Resource Starvation Detection
 * @description 檢查是否存在可能導致資源飢餓（例如忙碌的無限迴圈）的情形。
 * @kind problem
 * @id cpp/resource-starvation
 * @tags security
 */
import cpp

from WhileStmt whileStmt
where whileStmt.getCondition().toString() = "true" and
      whileStmt.getBody().toString().regexpMatch(".*;")
select whileStmt, "請確認此迴圈是否可能導致資源飢餓。"
