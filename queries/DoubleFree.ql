/**
 * @name Double Free Detection
 * @description 檢查是否存在對同一記憶體區塊重複釋放的情形。
 * @kind problem
 * @id cpp/double-free
 * @tags security
 */
import cpp

from Expr firstFree, Expr secondFree
where 
  firstFree.toString().regexpMatch("delete\\s+\\w+") and 
  secondFree.toString().regexpMatch("delete\\s+\\w+") and 
  firstFree.getSourceLocation() < secondFree.getSourceLocation() and
  firstFree.toString() = secondFree.toString()
select firstFree, "檢查是否對記憶體進行了雙重釋放。"
