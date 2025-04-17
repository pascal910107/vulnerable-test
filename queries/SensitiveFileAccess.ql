/**
 * @name Sensitive File Access Detection
 * @description 檢查是否存在對敏感檔案（例如 /etc/shadow）的硬編碼存取。
 * @kind problem
 * @id cpp/sensitive-file-access
 * @tags security
 */
import cpp

from StringLiteral lit
where lit.getStringValue().regexpMatch("(/etc/shadow)")
select lit, "請確認是否存在對敏感檔案未授權存取的情形。"
