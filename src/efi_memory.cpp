#include "efi_memory.h"

const char* EFI_MEMORY_TYPE_STRINGS[]
{
	"efi_reserved_memory_type",
	"efi_loader_code",
	"efi_loader_data",
	"efi_boot_services_code",
	"efi_boot_services_data",
	"efi_runtime_services_code",
	"efi_runtime_services_data",
	"efi_conventional_memory",
	"efi_unusable_memory",
	"efi_acpi_reclaimable_memory",
	"efi_acpi_memory_nvs",
	"efi_memory_mapped_io",
	"efi_memory_mapped_io_port_space",
	"efi_pal_code"
};
