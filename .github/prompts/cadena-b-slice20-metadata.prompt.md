---
mode: agent
agent: vsa-orchestator
description: "Ejecuta Cadena B — sub-tasks slice20 metadata.json (issues #65, #66, #68, #69). Salta Fase 1 y Fase 2 — los issues ya existen."
---

## CONTEXTO DE EJECUCIÓN

**Proyecto:** `crumbsole-design/automata_teatral` (rama `main`)
**Backend:** Python 3.10 — pytest + mypy strict
**Tarea:** Completar las sub-tasks de `SLICE-20 metadata.json`. Los issues #64 (schema MetadataJson) y #67 (serialize_metadata_json) ya están ✅ cerrados. Quedan #65, #66, #68, #69.

---

## INSTRUCCIÓN AL ORQUESTADOR

**SALTA Fase 1 (vsa-planner) y Fase 2 (vsa-decomposer).** Los issues ya existen en GitHub. Ve DIRECTAMENTE a **Fase 3 — Implementación**.

**Lee cada issue con `github/issue_read`** antes de delegarlo al coder.

**NOTA:** #65 y #66 son PARALELOS (sin dependencia entre sí). Ejecutarlos en secuencia está bien, pero no hay bloqueo. #69 requiere #64–#68 TODOS completados.

---

## CADENA DE ISSUES A EJECUTAR

| Orden | Issue | Descripción | Bloqueado por |
|-------|-------|-------------|---------------|
| 1     | #65   | `generate_unique_cue_id()` — generación de IDs únicos para cues | ✅ #64 |
| 2     | #66   | `validate_sequence_event()` — validación de eventos de secuencia | ✅ #64 (paralelo a #65) |
| 3     | #68   | `save_metadata_json_locally()` — persistencia local del JSON | ✅ #67 |
| 4     | #69   | Integration test e2e — flujo completo metadata.json | #64 + #65 + #66 + #67 + #68 |

---

## CONTEXTO DE CÓDIGO EXISTENTE

### Schema MetadataJson (src/api/gateway.py) — ✅ COMPLETADO en #64

**TypedDicts definidos:**
```python
class Capture(TypedDict):
    captureId: str
    fileName: str
    durationMs: int

class SequenceEvent(TypedDict, total=False):
    eventId: str
    delayMs: int
    type: str           # "evento_audio" | "evento_telon"
    assetName: str
    fader: Dict[str, Any]
    command: str         # "COMANDO_ABRIR" | "COMANDO_CERRAR" | "COMANDO_ESCENA" | None

class Cue(TypedDict):
    cueId: str
    labelText: str
    captures: List[Capture]
    sequence: List[SequenceEvent]

class MetadataJson(TypedDict):
    projectInfo: Dict[str, str]
    cues: List[Cue]
```

**JSON Schema generador:**
```python
def generate_metadata_json_schema() -> Dict[str, Any]:
    # Retorna JSON Schema draft-07 completo para MetadataJson
```

### Estructura de archivos relevante
```
src/
├── api/
│   └── gateway.py         ← MetadataJson TypeDicts + schema generator (✅ #64)
├── data/
│   ├── ingest.py          ← DataIngestor
│   ├── store.py           ← TemporalStore
│   └── transform.py       ← transforms
tests/
├── api/
│   └── test_gateway.py    ← test_generate_metadata_json_schema_exact_match
```

### Contrato del metadata.json (docs/contrato iniciador -editor.md)

**Campos `SequenceEvent.type` válidos:**
- `"evento_audio"` — evento de reproducción de audio
- `"evento_telon"` — evento de control del telón BLE

**Campos `SequenceEvent.command` válidos (solo para evento_telon):**
- `"COMANDO_ABRIR"`
- `"COMANDO_CERRAR"`
- `"COMANDO_ESCENA"`
- `None`

**`cueId` format esperado:** UUID v4 o similar ID único generado por `generate_unique_cue_id()`.

---

## SEÑALES DE SELECCIÓN DE CODER

Todos los issues #65, #66, #68, #69 son Python. Usar **`vsa-tdd-python-coder`** para todos.

---

## COMANDO DE TESTS

```bash
.venv\Scripts\Activate.ps1; pytest tests/api/ tests/data/ -v --tb=short
```

Suite completa:
```bash
.venv\Scripts\Activate.ps1; pytest tests/ -v --tb=short
```

---

## NOTAS PARA EL CODER

1. **`generate_unique_cue_id()` (#65):** Ubicación probable: `src/api/gateway.py` o nuevo archivo `src/data/metadata.py`. Usar `uuid.uuid4()` o similar. Debe ser determinista en tests (fijar seed o mock).
2. **`validate_sequence_event()` (#66):** Validar que `type` sea uno de `["evento_audio", "evento_telon"]`. Si `type == "evento_telon"`, `command` debe ser uno de los valores válidos. Usar el JSON Schema de #64 como referencia.
3. **`save_metadata_json_locally()` (#68):** Escribir `MetadataJson` como JSON a disco. Usar `json.dump()` con `ensure_ascii=False` y `indent=2`. Path configurable.
4. **Integration test (#69):** Flujo completo: generar IDs → construir `MetadataJson` → validar → serializar → guardar → leer de disco → verificar integridad.
5. **NO romper tests existentes** — `test_generate_metadata_json_schema_exact_match` en `tests/api/test_gateway.py` debe seguir verde.

---

## DEFINICIÓN DE DONE (DoD) POR ISSUE

- Test RED creado y falla
- Implementación mínima GREEN
- REFACTOR + `mypy`
- Todos los tests verdes sin regresiones
- Issue cerrado en GitHub con comentario de resumen
- Notificación ntfy enviada
