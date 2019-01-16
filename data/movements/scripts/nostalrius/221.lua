function onStepIn(creature, item, position, fromPosition)
	doRelocate({x = 32481, y = 31904, z = 04},{x = 32481, y = 31904, z = 05})
	Game.sendMagicEffect({x = 32481, y = 31904, z = 05}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32481, y = 31904, z = 04},{x = 32481, y = 31904, z = 05})
	Game.sendMagicEffect({x = 32481, y = 31904, z = 05}, 11)
end
