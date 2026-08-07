const normalizeScanfPrompt = (source) => {
  return source.replace(/scanf\(\s*"([^"]*)%([^"]*)"\s*,/g, (match, prefix, suffix) => {
    const prompt = prefix || '';
    if (!prompt.trim()) {
      return `fflush(stdout); scanf("%${suffix}",`;
    }

    const escapedPrompt = prompt.replace(/\\/g, '\\\\').replace(/"/g, '\\"');
    return `printf("${escapedPrompt}"); fflush(stdout); scanf("%${suffix}",`;
  });
};

module.exports = {
  normalizeScanfPrompt,
};
