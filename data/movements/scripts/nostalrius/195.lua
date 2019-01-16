function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32812, y = 31577, z = 05})
	Game.sendMagicEffect({x = 32812, y = 31577, z = 05}, 11)
end
