---
name: gh-common
description: Comandos gh CLI y git más usados por los agentes VSA. Cubre el 95% de operaciones habituales. Si necesitas algo no listado aquí (releases, codespaces, rulesets, etc.), usa .github/skills/gh-cli.md
---

# gh CLI — Comandos Frecuentes (mini-skill)

> REGLA: Usa SIEMPRE estos comandos via `execute/runInTerminal`. NUNCA uses `github/*` MCP tools.
> Si el comando que necesitas no aparece aquí → lee `.github/skills/gh-cli.md`.

---

## Issues

```bash
# Crear issue
gh issue create --title "TÍTULO" --body "CUERPO" --label "etiqueta1,etiqueta2"

# Listar issues abiertos
gh issue list --state open

# Listar issues por label
gh issue list --label "vsa-slice-pending"

# Ver issue
gh issue view 123

# Ver issue con comentarios
gh issue view 123 --comments

# Añadir comentario
gh issue comment 123 --body "COMENTARIO"

# Cerrar issue con comentario
gh issue close 123 --comment "Motivo de cierre"

# Reabrir issue
gh issue reopen 123

# Editar labels de un issue
gh issue edit 123 --add-label "etiqueta" --remove-label "otra-etiqueta"

# Editar título o body
gh issue edit 123 --title "Nuevo título"
gh issue edit 123 --body "Nuevo cuerpo"
```

---

## Pull Requests

```bash
# Crear PR (desde rama actual)
gh pr create --title "TÍTULO" --body "CUERPO" --base main

# Crear PR como draft
gh pr create --title "TÍTULO" --body "CUERPO" --draft

# Listar PRs abiertos
gh pr list --state open

# Ver PR
gh pr view 123

# Mergear PR (squash)
gh pr merge 123 --squash --delete-branch

# Mergear PR (merge commit)
gh pr merge 123 --merge --delete-branch
```

---

## Git

```bash
# Staging y commit
git add .
git add ruta/archivo.py
git commit -m "tipo(scope): descripción [skip ci]"

# Push
git push
git push origin nombre-rama

# Pull
git pull
git pull origin main

# Nueva rama y push
git checkout -b nombre-rama
git push -u origin nombre-rama

# Estado
git status
git log --oneline -5
```

---

## Combinados frecuentes (copy-paste ready)

```bash
# Commit + push (workflow habitual tras implementar tarea)
git add .
git commit -m "feat(slice): implementar {nombre_tarea}"
git push

# Crear issue slice y obtener su número
gh issue create --title "[SLICE] Nombre" --body "Descripción" --label "vsa-slice-pending"
gh issue list --label "vsa-slice-pending" --state open --json number,title

# Cerrar slice tras auditoría exitosa
gh issue comment 123 --body "✅ Slice completado. Todas las tareas implementadas y auditadas."
gh issue close 123

# Crear sub-tarea de un slice
gh issue create --title "nombre_slice_01_nombre_tarea" --body "SPEC_JSON aquí" --label "vsa-task-pending"
```
