/**
 * @name Hard-Coded Credentials Detection
 * @description 檢查是否存在硬編碼的密碼、使用者名稱等認證資訊。
 * @kind problem
 * @id cpp/hardcoded-credentials
 * @tags security
 */
import cpp

from StringLiteral lit
where lit.getStringValue().regexpMatch(".*(password|passwd|user).*")
select lit, "請避免直接硬編碼認證資訊。"
