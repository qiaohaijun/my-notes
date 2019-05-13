#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"

using namespace tensorflow;
using std::cout;
using std::vector;
using std::pair;

int main(int argc, char* argv[]) {
  // Initialize a tensorflow session
  Session* session;
  Status status = NewSession(SessionOptions(), &session);
  if (!status.ok()) {
    cout << status.ToString() << "\n";
    return 1;
  }

  // Read in the protobuf graph we exported
  // (The path seems to be relative to the cwd. Keep this in mind
  // when using `bazel run` since the cwd isn't where you call
  // `bazel run` but from inside a temp folder.)
  cout << "READING MODEL.\n";
  GraphDef graph_def;
  status = ReadBinaryProto(Env::Default(), "saved_model.pb", &graph_def);
  if (!status.ok()) {
    cout << status.ToString() << "\n";
    return 1;
  }
  cout << "DONE reading model.\n";
}
