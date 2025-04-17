/**
 * @name Information Disclosure Detection
 * @description 檢查是否有直接打印可能洩露敏感資訊的情形。
 * @kind problem
 * @id cpp/info-disclosure
 * @tags security
 */
import cpp

from CallExpr call
where call.getTarget().(Function).getName() in ["printf", "std::cout"] and 
      call.toString().regexpMatch(".*(password|secret|credential).*")
select call, "請確認輸出中是否包含敏感資訊，避免洩漏。"
