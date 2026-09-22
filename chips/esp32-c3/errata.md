<!-- source: https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/03-errata-description/index.html | fetched: 2026-09-22 -->
# All Errata Descriptions - ESP32-C3 -  — ESP Chip Errata latest documentation

# All Errata Descriptions

[[中文]](https://docs.espressif.com/projects/esp-chip-errata/zh_CN/latest/esp32c3/03-errata-description/index.html)

## [CPU-863] Misaligned Memory Access May Lead to Exception

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-2.html) [v0.3](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-3.html) [v0.4](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-4.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v1-1.html)

### Description

A misaligned **load** instruction immediately followed by a **store** instruction may raise a load access fault exception (exception code 5) when the load address and the store address lie in regions with different access permissions configured via Physical Memory Protection (PMP) or Physical Memory Attributes (PMA).

For example, the following sequence commonly triggers this issue when copying an unaligned word from flash or ROM into RAM:

```
lw  a0, 0(a1)   # unaligned 32-bit address load from a read-only PMP region (e.g., ROM)
sw  a0, 0(a2)   # store to a read-write PMP region (e.g., RAM)
```

**Root cause:**

A misaligned **load** that crosses a word boundary is split internally into two transactions. Due to a timing alignment issue in the design, the second transaction of the misaligned **load** can incorrectly be checked against the store’s access permissions instead of its own, triggering an exception.

### Workarounds

The RISC-V specification does not guarantee that hardware supports misaligned accesses. General-purpose RISC-V code should not rely on that support. If misaligned accesses cannot be avoided, such as when porting third-party libraries, use the following workarounds:

- Insert one or more **nop** instructions between the misaligned **load** and the following **store**. This prevents the incorrect permission check described above.

  Note

  Linkers that support the `--fix-esp-pmp-misalign` option can insert **nop** instructions between consecutive **load** and **store** instructions automatically. This option is conservative, as it may also insert extra **nop** instructions for pairs that would not trigger this exception, for example, when the accesses are aligned or when both access the same PMP region.
- When copying memory, use misaligned **load**/**store** only for the first and last misaligned words of a data block, and use aligned **load**/**store** for the words in between. This approach requires fewer **nop** instructions and has better performance than inserting **nop** instructions throughout.
- Configure the same PMP/PMA permissions for the memory regions accessed by the misaligned **load** and the following **store**. This may require saving and restoring the permission settings around the affected code.

### Solution

No fix scheduled.

## [ADC-183] The Digital Controller (DMA) of SAR ADC2 Cannot Work

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-2.html) [v0.3](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-3.html) [v0.4](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-4.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v1-1.html)

### Description

The Digital Controller of SAR ADC2, i.e., DIG ADC2 controller, may receive a false sampling enable signal. In such a case, the controller will enter an inoperative state.

### Workarounds

It is suggested to use SAR ADC1.

### Solution

No fix scheduled.

## [ADC-270] SAR ADC Cannot Sample Sufficient Data in DMA Continuous Conversion Mode After Restart

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-2.html) [v0.3](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-3.html) [v0.4](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v0-4.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c3/_tags/v1-1.html)

### Description

In DMA continuous conversion mode, if the SAR ADC is stopped and then restarted, the internal hardware counter that counts ADC samples will not be automatically cleared, and there is no dedicated register to manually clear it.

Consequently, users might encounter scenarios such as:

- Garbled sampling results
- Samples fewer than the configured value

### Workarounds

Before starting the ADC continuous conversion:

1. Reset the ADC by first setting and then clearing SYSTEM\_APB\_SARADC\_RST
2. Sequentially configure the 16-bit APB\_SARADC\_APB\_ADC\_EOF\_NUM field with all values ranging from the previously configured value down to 0, so as to clear the ADC sample counter

Note that this flow may take around 14 ms at most.

### Solution

No fix scheduled.
