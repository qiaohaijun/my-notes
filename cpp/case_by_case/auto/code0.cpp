  auto it = client_library.compile_only_instances_.find(platform->id());
  if (it != client_library.compile_only_instances_.end()) {
    return it->second->client.get();
  }

  auto instance = MakeUnique<CompileOnlyInstance>();
  TF_ASSIGN_OR_RETURN(instance->service,
                      CompileOnlyService::NewService(platform));
  instance->client = MakeUnique<CompileOnlyClient>(instance->service.get());
  CompileOnlyClient* cl = instance->client.get();

  client_library.compile_only_instances_.insert(
      std::make_pair(platform->id(), std::move(instance)));
  return cl;
