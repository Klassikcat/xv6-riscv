-- xv6 project specific settings
-- Disable auto formatting for this project to preserve kernel code style

vim.api.nvim_create_autocmd("BufWritePre", {
  pattern = "*.c,*.h",
  callback = function()
    -- Disable format on save for C files in this project
    return
  end,
  group = vim.api.nvim_create_augroup("xv6_no_format", { clear = true })
})

-- Disable LSP formatting for this buffer
vim.api.nvim_create_autocmd("LspAttach", {
  callback = function(args)
    local client = vim.lsp.get_client_by_id(args.data.client_id)
    if client and client.name == "clangd" then
      client.server_capabilities.documentFormattingProvider = false
      client.server_capabilities.documentRangeFormattingProvider = false
    end
  end,
  group = vim.api.nvim_create_augroup("xv6_disable_lsp_format", { clear = true })
})