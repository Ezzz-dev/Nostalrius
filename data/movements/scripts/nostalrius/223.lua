function onStepIn(creature, item, position, fromPosition)
	doRelocate({x = 32479, y = 31904, z = 02},{x = 32479, y = 31904, z = 03})
	Game.sendMagicEffect({x = 32479, y = 31904, z = 03}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32479, y = 31904, z = 02},{x = 32479, y = 31904, z = 03})
	Game.sendMagicEffect({x = 32479, y = 31904, z = 03}, 11)
end
