LocalClientOptions& LocalClientOptions::set_platform(
    perftools::gputools::Platform* platform) {
  platform_ = platform;
  return *this;
}

perftools::gputools::Platform* LocalClientOptions::platform() const {
  return platform_;
}

LocalClientOptions& LocalClientOptions::set_number_of_replicas(
    int number_of_replicas) {
  number_of_replicas_ = number_of_replicas;
  return *this;
}

int LocalClientOptions::number_of_replicas() const {
  return number_of_replicas_;
}

LocalClientOptions& LocalClientOptions::set_intra_op_parallelism_threads(
    int num_threads) {
  intra_op_parallelism_threads_ = num_threads;
  return *this;
}

