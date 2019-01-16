function onStepIn(creature, item, position, fromPosition)
	doRelocate({x = 32476, y = 31904, z = 03},{x = 32476, y = 31904, z = 04})
	Game.sendMagicEffect({x = 32476, y = 31904, z = 04}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32476, y = 31904, z = 03},{x = 32476, y = 31904, z = 04})
	Game.sendMagicEffect({x = 32476, y = 31904, z = 04}, 11)
end
