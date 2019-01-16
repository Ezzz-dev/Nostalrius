function onStepIn(creature, item, position, fromPosition)
	item:transform(430, 1)
	item:decay()
	Game.transformItemOnMap({x = 32915, y = 32079, z = 5}, 2114, 2113)
end

function onStepOut(creature, item, position, fromPosition)
	item:transform(431, 1)
	item:decay()
	Game.transformItemOnMap({x = 32915, y = 32079, z = 5}, 2113, 2114)
end
