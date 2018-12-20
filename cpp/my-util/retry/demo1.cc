CassRetryPolicy* fallthrough_policy =
cass_retry_policy_fallthrough_new();

/* ... */

/* Retry policies must be freed */
cass_retry_policy_free(fallthrough_policy);

CassRetryPolicy* default_policy = cass_retry_policy_default_new();
CassRetryPolicy* logging_policy = cass_retry_policy_logging_new(default_policy)

cass_cluster_set_retry_policy(cluster, logging_policy);

/* ... */

/* Retry policies must be freed */
cass_retry_policy_free(default_policy);
cass_retry_policy_free(logging_policy);
