duel_sources = [
  'main.c',
  'duel-application.c',
  'duel-window.c',
]

duel_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.2'),
]

duel_sources += gnome.compile_resources('duel-resources',
  'duel.gresource.xml',
  c_name: 'Duel'
)

executable('duel', duel_sources,
  dependencies: duel_deps,
       install: true,
)
