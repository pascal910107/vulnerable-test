/**
 * @name Unchecked Input Vulnerability
 * @description 檢查是否使用不安全的輸入函式（例如 gets）。
 * @kind problem
 * @id cpp/unchecked-input
 * @tags security
 */
import cpp

from CallExpr call
where call.getTarget().(Function).getName() = "gets"
select call, "使用 gets 輸入不安全，請改用更安全的替代方案，例如 fgets。"
