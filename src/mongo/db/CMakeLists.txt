add_subdirectory(auth)

add_library(mongohasher STATIC
  hasher
  )
add_dependencies(mongohasher generate_error_codes generate_action_types)

add_library(server_parameters STATIC
  server_parameters
  )
add_dependencies(server_parameters generate_error_codes generate_action_types)
target_link_libraries(server_parameters foundation bson)

add_library(index_set STATIC
  index_set
  )

add_library(dbcmdline STATIC
  cmdline
  )
target_link_libraries(dbcmdline LINK_PRIVATE
  bson
  server_parameters
  )

add_library(db_common STATIC
  field_ref
  )
target_link_libraries(db_common LINK_PRIVATE
  bson
  foundation
  )

add_library(coredb STATIC
  ../client/parallel
  client_transaction
  opsettings
  commands.cpp
  commands/authentication_commands
  commands/connection_status
  commands/fail_point_cmd
  commands/find_and_modify_common
  commands/hashcmd
  commands/isself
  commands/mr_common
  commands/rename_collection_common
  commands/parameters
  commands/server_status
  pipeline/pipeline
  dbcommands_generic
  dbpath
  dbwebserver
  keypattern
  keygenerator
  matcher
  txn_context
  gtid
  pipeline/accumulator
  pipeline/accumulator_add_to_set
  pipeline/accumulator_avg
  pipeline/accumulator_first
  pipeline/accumulator_last
  pipeline/accumulator_min_max
  pipeline/accumulator_push
  pipeline/accumulator_single_value
  pipeline/accumulator_sum
  pipeline/builder
  pipeline/doc_mem_monitor
  pipeline/document
  pipeline/document_source
  pipeline/document_source_bson_array
  pipeline/document_source_command_shards
  pipeline/document_source_filter_base
  pipeline/document_source_geo_near
  pipeline/document_source_group
  pipeline/document_source_limit
  pipeline/document_source_match
  pipeline/document_source_out
  pipeline/document_source_project
  pipeline/document_source_skip
  pipeline/document_source_sort
  pipeline/document_source_unwind
  pipeline/expression
  pipeline/expression_context
  pipeline/field_path
  pipeline/value
  projection
  querypattern
  queryutil
  stats/timer_stats
  stats/top
  descriptor
  storage/cursor
  storage/txn
  storage/env
  storage/key
  ../s/shardconnection
  )
add_dependencies(coredb generate_error_codes generate_action_types install_tdb_h)
target_link_libraries(coredb LINK_PRIVATE
  serverauth
  db_common
  mongocommon
  dbcmdline
  coreserver
  plugins
  server_parameters
  foundation
  ${TokuKV_LIBRARIES}
  )

add_library(serveronly STATIC
  curop
  kill_current_op
  interrupt_status_mongod
  d_globals
  ttl
  d_concurrency
  lockstat
  lockstate
  introspect
  clientcursor
  repl.cpp
  oplogreader
  repl/rs
  repl/consensus
  repl/rs_initiate
  repl/replset_commands
  repl/manager
  repl/health
  repl/heartbeat
  repl/rs_config
  repl/rs_sync
  repl/rs_initialsync
  repl/bgsync
  oplog
  oplog_helpers
  repl_block
  indexcursor
  cloner
  indexer
  namespace_details
  namespace_index
  txn_complete_hooks
  matcher_covered
  dbeval
  restapi
  dbhelpers
  instance
  client
  client_load
  database
  cursor
  query_optimizer
  query_optimizer_internal
  queryoptimizercursorimpl
  query_plan
  query_plan_selection_policy
  parsed_query
  index
  scanandorder
  explain
  ops/count
  ops/delete
  ops/query
  ops/update
  ops/update_internal
  ops/insert

  # most commands are only for mongod
  dbcommands
  commands/dbcommands_deprecated
  commands/fsync
  commands/distinct
  commands/find_and_modify
  commands/group
  commands/mr
  commands/pipeline_command
  commands/txn_commands
  commands/load
  commands/testhooks
  pipeline/pipeline_d
  pipeline/document_source_cursor

  # Most storage/ files are in coredb, but this is server-only.
  storage/loader
  storage/indexer
  storage/dictionary
  
  ../util/elapsed_tracker
  stats/snapshots
  ../s/d_logic
  ../s/d_writeback
  ../s/d_migrate
  ../s/d_state
  ../s/d_split
  ../client/distlock_test
  ../s/d_chunk_manager
  module
  )
add_dependencies(serveronly generate_error_codes generate_action_types install_tdb_h)
target_link_libraries(serveronly LINK_PRIVATE
  coreshard
  authmongod
  db_common
  defaultversion
  index_set
  ${TokuKV_LIBRARIES}
  )

add_library(mongodandmongos STATIC
  connection_factory
  initialize_server_global_state
  server_extra_log_context
  ../util/net/message_server_port
  )
add_dependencies(mongodandmongos generate_error_codes generate_action_types install_tdb_h)

add_library(coreserver STATIC
  client_basic
  common
  ../util/net/miniwebserver
  stats/counters
  stats/service_stats
  )
add_dependencies(coreserver generate_error_codes generate_action_types)
target_link_libraries(coreserver LINK_PRIVATE
  mongocommon
  scripting
  systeminfo
  )

if (BUILD_TESTING)
  foreach (test
      cmdline_test
      field_ref_test
      index_set_test
      server_parameters_test
      )
    add_executable(${test} ${test})
    add_dependencies(${test} generate_error_codes generate_action_types)
    target_link_whole_libraries(${test}
      unittest_main
      foundation
      unittest_crutch
      base
      )
    add_test(mongo/db/${test} ${test})
  endforeach ()

  target_link_libraries(cmdline_test dbcmdline)
  target_link_libraries(field_ref_test db_common)
  target_link_libraries(index_set_test bson index_set)
  target_link_libraries(server_parameters_test server_parameters)
endif ()